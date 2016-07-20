//
//  ScriptParser.hpp
//  ComponentSystem
//
//  Created by Jeppe Nielsen on 31/01/16.
//  Copyright © 2016 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "ScriptClass.hpp"
#include <vector>

namespace Pocket {

class ScriptParser {
public:
    bool ParseCode(ScriptClass& root, std::vector<std::string> cppFiles, std::vector<std::string> includePaths);
    ScriptClass ExtractSystemsAndComponents(const ScriptClass& root);
};

}
