//
//  GameScene.hpp
//  TestComponentSystem
//
//  Created by Jeppe Nielsen on 18/10/16.
//  Copyright © 2016 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include <vector>
#include "GameObject.hpp"
#include "Property.hpp"

namespace Pocket {
    class GameWorld;
    class IGameSystem;
    class GameScene {
    private:
        friend class GameWorld;
        friend class GameObject;
        friend class std::allocator<GameScene>;
        
        using Actions = std::deque<std::function<void()>>;
        Actions delayedActions;
        
        GameWorld* world;
        int index;
        std::vector<IGameSystem*> systemsIndexed;
        std::vector<IGameSystem*> activeSystems;
        
        GameObject root;
        bool removed;
        
        GameScene();
        ~GameScene();
        GameScene(const GameScene& other);
        void DoActions(Actions &actions);
        void Update(float dt);
        void Render();
        
        friend class Container<GameScene>;
    public:
        Property<bool> Active;
        const GameObject* Root();
        GameObject* CreateObject();
        void Remove();
        void Clear();
        
        Handle<GameScene> GetHandle();
    };
}