//
//  OpenWorldCollection.hpp
//  PocketEditor
//
//  Created by Jeppe Nielsen on 13/09/16.
//  Copyright © 2016 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include <vector>
#include <string>
#include "OpenWorld.hpp"
#include "Property.hpp"

using namespace Pocket;

class OpenWorldCollection {
public:
    OpenWorld* LoadWorld(const std::string& path);
    void CloseWorld(OpenWorld* world);
    
    OpenWorldCollection();
    ~OpenWorldCollection();
    
    Property<OpenWorld*> ActiveWorld;
    
    void Clear();
    
    void Initialize(InputManager& input);
    
private:
    using Worlds = std::vector<OpenWorld*>;
    Worlds worlds;
    InputManager* input;
};