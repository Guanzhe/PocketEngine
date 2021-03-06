//
//  Movable.h
//  Homeland
//
//  Created by Jeppe Nielsen on 23/07/15.
//  Copyright (c) 2015 Jeppe Nielsen. All rights reserved.
//

#pragma once

#include "GameWorld.hpp"
#include "Vector3.hpp"

using namespace Pocket;

struct Movable {
public:
    Movable();
    float Speed;
    typedef std::vector<Vector2> Path;
    Path path;
    void Reset();
    Property<Vector2> Target;

    Vector2 prevPosition;
    int stillFrames;
};
