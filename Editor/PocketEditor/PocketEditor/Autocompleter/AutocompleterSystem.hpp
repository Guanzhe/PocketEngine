//
//  AutocompleterSystem.hpp
//  PocketEditor
//
//  Created by Jeppe Nielsen on 19/04/2017.
//  Copyright © 2017 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "GameSystem.hpp"
#include "Autocompleter.hpp"
#include "TextEditor.hpp"
#include "CodeFile.hpp"
#include "Worker.hpp"

using namespace Pocket;

struct AutocompleterSystem : public GameSystem<CodeFile, Autocompleter, TextEditor> {
    
    void Initialize() override;
    void Destroy() override;
    
    void ObjectAdded(GameObject* object) override;
    void ObjectRemoved(GameObject* object) override;
    void OnAutoCompleteEnabled(GameObject* object);
    void Update(float dt) override;
private:
    
    Worker worker;
};
