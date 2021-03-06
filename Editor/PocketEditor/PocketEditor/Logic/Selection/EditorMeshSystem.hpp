//
//  EditorSelectionSystem.hpp
//  PocketEditor
//
//  Created by Jeppe Nielsen on 06/04/16.
//  Copyright © 2016 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "GameSystem.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"
#include "Selectable.hpp"
#include <map>
#include <set>

using namespace Pocket;

class EditorMeshSystem : public GameSystem<Transform, Mesh, Selectable> {
public:
    void ObjectAdded(GameObject* object);
    void ObjectRemoved(GameObject* object);
    void Update(float dt);
private:
    void SelectionChanged(GameObject* object);
    void TryRemoveTransformObject(GameObject* object);
    using TransformObjects = std::map<GameObject*, GameObject*>;
    TransformObjects transformObjects;
    
    void BoundingBoxDirty(GameObject* object);
    void CreateMesh(GameObject* object);
    
    std::set<GameObject*> dirtyObjects;
};
