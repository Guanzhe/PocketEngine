//
//  GameObjectEditorSystem.h
//  GUIEditor
//
//  Created by Jeppe Nielsen on 24/09/15.
//  Copyright (c) 2015 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "GameWorld.hpp"
#include "GameObjectEditor.hpp"
#include "Transform.hpp"
#include "Sizeable.hpp"
#include "Gui.hpp"
#ifdef SCRIPTING_ENABLED
#include "ScriptWorld.hpp"
#endif

namespace Pocket {
    class GameObjectEditorSystem : public GameSystem<GameObjectEditor, Transform, Sizeable> {
        public:
            GameObjectEditorSystem();
            void Initialize();
        
            Gui* gui;
#ifdef SCRIPTING_ENABLED
            ScriptWorld* scriptWorld;
#endif
            void ObjectAdded(GameObject* object);
            void ObjectRemoved(GameObject* object);
        
            template<class T>
            void IgnoreComponent() {
                ignoredComponents.push_back(GameIDHelper::GetComponentID<T>());
            }
        private:
            void ObjectChanged(GameObject* object);
            typedef std::vector<int> IgnoredComponents;
            IgnoredComponents ignoredComponents;
    };
}