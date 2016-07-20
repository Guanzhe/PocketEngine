//
//  Project.hpp
//  PocketEditor
//
//  Created by Jeppe Nielsen on 05/04/16.
//  Copyright © 2016 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "GameWorld.hpp"
#include "Transform.hpp"
#include "InputManager.hpp"
#include "ScriptWorld.hpp"
#include <vector>

using namespace Pocket;

class Project {
private:
    GameWorld world;
    ScriptWorld scriptWorld;
    std::string path;
    std::vector<std::string> defaultIncludes;
public:
    Project();
    void CreateNew(const std::string& path);
    GameWorld& World();
    ScriptWorld& ScriptWorld();
    void CreateDefaultScene(GameWorld& editorWorld, GameObject* gameRoot, InputManager& input);
    bool Compile();
    void Build();
};