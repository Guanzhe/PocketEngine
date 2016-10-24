//
//  GameWorld.hpp
//  TestComponentSystem
//
//  Created by Jeppe Nielsen on 17/10/16.
//  Copyright © 2016 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include <vector>
#include <functional>
#include "MetaLibrary.hpp"
#include "Container.hpp"
#include "TypeInfo.hpp"
#include "GameIdHelper.hpp"
#include "GameObject.hpp"
#include "IGameSystem.hpp"
#include "GameScene.hpp"
#include "InputManager.hpp"

namespace Pocket {

    class ScriptWorld;
    
    class GameWorld {
    private:
        
        struct ComponentInfo {
            ComponentInfo() : container(0), getTypeInfo(0) {}
            IContainer* container;
            std::string name;
            std::function<TypeInfo(GameObject*)> getTypeInfo;
            std::vector<int> systemsUsingComponent;
        };
    
        using Components = std::vector<ComponentInfo>;
        Components components;
        
        struct SystemInfo {
            SystemInfo() : createFunction(0), deleteFunction(0) {}
            Bitset bitset;
            std::function<IGameSystem*(GameObject*)> createFunction;
            std::function<void(IGameSystem*)> deleteFunction;
        };
        
        using Systems = std::vector<SystemInfo>;
        Systems systems;
        
        Container<GameObject> objects;
        int componentTypesCount;
        
        Container<GameScene> scenes;
        std::vector<GameScene*> activeScenes;
        std::vector<GameObject*> roots;
        
        using Actions = std::deque<std::function<void()>>;
        Actions delayedActions;
        
        InputManager input;
        
        using ComponentTypeFunction = std::function<void(ComponentInfo&)>;
        using SystemTypeFunction = std::function<void(SystemInfo&, std::vector<ComponentId>&)>;
    
        void AddComponentType(ComponentId componentId, const ComponentTypeFunction& function);
        void AddSystemType(SystemId systemId, const SystemTypeFunction& function);
        void RemoveSystemType(SystemId systemId);

        void DoActions(Actions &actions);
        void RemoveRoot(GameObject* root);
                
    public:
    
        GameWorld();
        ~GameWorld();
    
        template<typename T>
        void AddComponentType() {
            AddComponentType(GameIdHelper::GetComponentID<T>(), [] (ComponentInfo& componentInfo) {
                componentInfo.container = new Container<T>();
                componentInfo.name = GameIdHelper::GetClassName<T>();
                T* ptr;
                Meta::static_if<Meta::HasGetTypeFunction::apply<T>::value, T*>(ptr, [&componentInfo](auto p) {
                    using SerializedComponentType = typename std::remove_pointer<decltype(p)>::type;
                    componentInfo.getTypeInfo = [](GameObject* object) -> TypeInfo {
                        auto component = object->GetComponent<SerializedComponentType>();
                        return component->GetType();
                    };
                });
            });
        }
    
        template<typename T>
        void AddSystemType() {
            AddSystemType(GameIdHelper::GetSystemID<T>(), [this] (SystemInfo& systemInfo, std::vector<ComponentId>& components) {
                T::ExtractAllComponents(*this, components);
                systemInfo.createFunction = [] (GameObject* root) {
                    T* system = new T();
                    GameObject** systemRoot = ((GameObject**)&system->root);
                    *(systemRoot) = root;
                    return system;
                };
                systemInfo.deleteFunction = [] (IGameSystem* system) {
                    delete ((T*)system);
                };
            });
        }
        
        GameObject* CreateRoot();
        
        const ObjectCollection& Roots();
        
        void Update(float dt);
        void Render();
        
        void Clear();
        
        int ObjectCount();
        
        InputManager& Input();
        
        friend class GameScene;
        friend class GameObject;
        friend class ScriptWorld;
    };
    
    class SubSystemCreator {
    private:
        friend class GameWorld;
        GameWorld* world;
    public:
        template<typename T>
        void AddSystemType() {
            world->AddSystemType<T>();
        }
    };
}