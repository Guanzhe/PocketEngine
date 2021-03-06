//
//  ParticleSystem.cpp
//  CraneCreator
//
//  Created by Jeppe Nielsen on 12/2/14.
//  Copyright (c) 2014 Jeppe Nielsen. All rights reserved.
//

#include "ParticleUpdaterSystem.h"
#include <cmath>
#include <iostream>

void ParticleUpdaterSystem::Simulate(float dt) {

    float damping = pow(0.35, dt);
    float gravity = -60 * dt * dt;

    for (auto it = Objects().begin(); it!=Objects().end(); it++) {
        
        GameObject* object = *it;
        Particle* particle = object->GetComponent<Particle>();
        if (particle->immovable) continue;
        
        Vector2 temp = particle->position;
        
        Vector2 offset = particle->position - particle->positionOld;
        
        particle->position += offset * damping + Vector2(0,gravity);
        
        particle->positionOld = temp;
    }
    
    for (auto it = Objects().begin(); it!=Objects().end(); it++) {
        GameObject* object = *it;
        Particle* particle = object->GetComponent<Particle>();
        if (particle->position.y<-100) {
            particle->position.y = -100;
            float xVel = particle->position.x - particle->positionOld.x;
            particle->position.x -= xVel * 0.5f;
        }
        /*
        if (particle->position.x<-60) {
            particle->position.x = -60;
        }
        if (particle->position.x>60) {
            particle->position.x = 60;
        }
        */
        
        if (particle->immovable) {
            particle->positionOld = particle->position;
        }
        
    }

    //std::cout<<" Particles:"<<Objects().size()<<std::endl;
}


