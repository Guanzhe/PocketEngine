//
//  TouchAnimatorSystem.h
//  PocketEngine
//
//  Created by Jeppe Nielsen on 9/9/14.
//  Copyright (c) 2014 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "GameWorld.hpp"
#include "Touchable.hpp"
#include "TouchAnimator.hpp"
#include "TransformAnimator.hpp"
#include "TransformAnimationDatabase.hpp"

namespace Pocket {
    class TouchAnimatorSystem : public GameSystem {
    public:
        void Initialize();
        void ObjectAdded(GameObject* object);
        void ObjectRemoved(GameObject* object);
        
    private:
        void Down(TouchData d, GameObject* object);
        void Up(TouchData d, GameObject* object);
        
    };
}