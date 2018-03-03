//
//  GameStorage.cpp
//  TestComponentSystem
//
//  Created by Jeppe Nielsen on 29/12/2017.
//  Copyright © 2017 Jeppe Nielsen. All rights reserved.
//

#include "GameStorage.hpp"
#include "GameScene.hpp"
#include "Hierarchy.hpp"
#include "GameWorld.hpp"
#include "GameObjectHandle.hpp"

using namespace Pocket;

GameStorage::GameStorage() : componentTypesCount(0), systemIdCounter(0), componentIdCounter(0) {
    objects.count = 0;
    AddComponentType<Hierarchy>();
    prefabWorld = new GameWorld();
    prefabWorld->Initialize(*this);
}

GameStorage::~GameStorage() {
    delete prefabWorld;
}

void GameStorage::AddComponentType(ComponentId componentId, const ComponentTypeFunction& function) {
    if (componentId>=components.size()) {
        componentTypesCount = componentId + 1;
        components.resize(componentTypesCount);
        
        if (objects.defaultObject.activeComponents.Size()<componentTypesCount) {
            objects.defaultObject.activeComponents.Resize(componentTypesCount);
            for(auto& o : objects.entries) {
                o.activeComponents.Resize(componentTypesCount);
                o.enabledComponents.Resize(componentTypesCount);
                o.componentIndicies.resize(componentTypesCount);
            }
        }
    }
    
    if (!components[componentId].container) {
        function(components[componentId]);
    }
}

void GameStorage::AddSystemType(SystemId systemId, const SystemTypeFunction& function, const std::function<void()>& finished) {
    if (systemId>=systems.size()) {
        systems.resize(systemId + 1);
    }
    
    SystemInfo& systemInfo = systems[systemId];
    
    if (!systemInfo.createFunction) {
        std::vector<ComponentId> componentIndices;
        function(systemInfo, componentIndices);
        Bitset systemBitset;
        for(auto c : componentIndices) {
            if (c>=systemBitset.Size()) {
                systemBitset.Resize(c + 1);
            }
            systemBitset.Set(c, true);
            components[c].systemsUsingComponent.push_back(systemId);
        }
        systemInfo.bitset = systemBitset;
        
        if (finished) {
            finished();
        }
    }
}

void GameStorage::RemoveSystemType(SystemId systemId) {
    SystemInfo& systemInfo = systems[systemId];
    if (!systemInfo.createFunction) return;
    scenes.Iterate([this, &systemInfo, systemId] (GameScene* scene) {
        if (systemId>=scene->systemsIndexed.size()) return;
        IGameSystem* system = scene->systemsIndexed[systemId];
        if (!system) return;
        if (system->ObjectCount()>0) {
            scene->IterateObjects([&systemInfo, system] (GameObject* object) {
                if ( systemInfo.bitset.Contains(object->enabledComponents)) {
                    system->ObjectRemoved(object);
                    system->RemoveObject(object);
                }
            });
            scene->world->RemoveActiveSystem(system);
        }
        systemInfo.deleteFunction(system);
        scene->systemsIndexed[systemId] = nullptr;
    });

    for(int i=0; i<systemInfo.bitset.Size(); ++i) {
        if (systemInfo.bitset[i]) {
            auto& list = components[i].systemsUsingComponent;
            list.erase(std::find(list.begin(), list.end(), systemId));
        }
    }
    systemInfo.createFunction = 0;
    systemInfo.deleteFunction = 0;
    systemInfo.bitset.Reset();
}

bool GameStorage::TryGetComponentIndex(const std::string& componentName, int& index) const {
    for(int i=0; i<components.size(); ++i) {
        if (components[i].name == componentName) {
            index = i;
            return true;
        }
    }
    return false;
}

bool GameStorage::TryGetComponentIndex(const std::string& componentName, int& index, bool& isReference) const {
    if (TryGetComponentIndex(componentName, index)) {
        isReference = false;
        return true;
    }
    if (componentName.size()>4) {
        size_t refLocation = componentName.rfind(":ref");
        if (refLocation!=-1) {
            std::string componentNameNoRef = componentName.substr(0, refLocation);
            if (TryGetComponentIndex(componentNameNoRef, index)) {
                isReference = true;
                return true;
            }
        }
    }
    return false;
}

ComponentTypeCollection GameStorage::GetComponentTypes() const {
    ComponentTypeCollection componentTypes;
    for(auto& c : components) {
        componentTypes.push_back({ c.name, c.getTypeInfo });
    }
    return componentTypes;
}

void GameStorage::SerializeAndRemoveComponents(std::ostream& stream, const SerializePredicate &predicate) {

    std::vector<GameObject*> objectsToSerialize;
    objects.Iterate([&objectsToSerialize](GameObject* object) {
        objectsToSerialize.push_back(object);
    });

    serializer->SerializeComponents(objectsToSerialize, stream, predicate);

    for(auto o : objectsToSerialize) {
        o->RemoveComponents(predicate);
        o->scene->world->DoActions(o->scene->world->delayedActions);
    }
}

void GameStorage::DeserializeAndAddComponents(std::istream &jsonStream) {
    std::vector<GameObject*> objectsToDeserialize;
    objects.Iterate([&objectsToDeserialize](GameObject* object) {
        objectsToDeserialize.push_back(object);
    });
    serializer->DeserializeAndAddComponents(objectsToDeserialize, jsonStream);
}

GameObject* GameStorage::TryGetPrefab(const std::string &guid, int objectId) {
    GameObject* scene = prefabWorld->FindScene(guid);
    
    if (!scene) {
        scene = GuidToRoot(guid);
    }
    
    if (scene) {
        return objectId == 1 ? scene : scene->scene->FindObject(objectId);
    } else {
        return nullptr;
    }
}

GameObject* GameStorage::LoadPrefab(const std::string &guid, std::istream &stream) {
    GameObject* prefab = prefabWorld->CreateScene();
    prefab->scene->guid = guid;
    if (PrefabLoaded) {
        PrefabLoaded(prefab);
    }
    serializer->Deserialize(prefab, stream);
    prefabWorld->Update(0.0f);
    return prefab;
}

void GameStorage::ApplyPrefab(Pocket::GameObject *prefab, Pocket::GameObject *scene) {
    assert(prefab->scene->world == prefabWorld);

    for (int i=0; i<componentTypesCount; i++) {
        if (GameIdHelper::GetComponentID<Hierarchy>()!=i) {
            prefab->RemoveComponent(i);
        }
    }
    for(auto child : prefab->Hierarchy().Children()) {
        child->Remove();
    }
    prefabWorld->Update(0.0f);
    prefab->ApplyClone(scene);
    InvokeChangeToHandles(prefab);
}

void GameStorage::TryParseComponent(std::istream &stream, int componentId,
    const std::function<void (int, int)>& callback,
    const std::function<bool (const std::string& componentName)>& componentCallback) const {
    serializer->TryParse(stream, componentId<0 ? "" : components[componentId].name, callback, componentCallback);
}


void GameStorage::InvokeChangeToHandles(Pocket::GameObject *object) {

    std::vector<GameObjectHandle*> handlesToChange;
    
    const std::string& id = object->RootGuid();
    
    for(GameObjectHandle* h : handles) {
        if (h->sceneGuid == id) {
           handlesToChange.push_back(h);
        }
    }
    
    for(auto h : handlesToChange) {
        h->Changed();
    }
}

