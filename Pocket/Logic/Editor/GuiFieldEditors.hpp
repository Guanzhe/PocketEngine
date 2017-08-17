//
//  SerializedFieldEditors.h
//  GUIEditor
//
//  Created by Jeppe Nielsen on 24/09/15.
//  Copyright (c) 2015 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "Gui.hpp"
#include "TextBox.hpp"
#include "TypeInfo.hpp"
#include "Property.hpp"
#include <vector>
#include <functional>

namespace Pocket {
    struct GuiFieldEditor : public IFieldEditor {
        void Create(const std::string& name, void* context, void* parent) override {
            Initialize(name, (Gui*)context, (GameObject*) parent);
        }
        virtual void Initialize(const std::string& name, Gui* gui, GameObject* object) = 0;
    };
}
