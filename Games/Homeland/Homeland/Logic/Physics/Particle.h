//
//  Particle.h
//  CraneCreator
//
//  Created by Jeppe Nielsen on 12/2/14.
//  Copyright (c) 2014 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "GameWorld.hpp"
#include "Vector2.hpp"
#include "NavMesh.hpp"

using namespace Pocket;

struct Particle {
    public:
    Particle();
        float mass;
        Vector2 position;
        Vector2 positionOld;
        bool immovable;

        void SetPosition(Vector2 position);

        NavTriangle* lastTriangle;
        int navMeshVersion;

};