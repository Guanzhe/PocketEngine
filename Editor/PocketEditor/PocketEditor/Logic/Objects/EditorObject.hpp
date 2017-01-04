//
//  EditorObject.hpp
//  PocketEditor
//
//  Created by Jeppe Nielsen on 14/04/16.
//  Copyright © 2016 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "GameWorld.hpp"

using namespace Pocket;

struct EditorObject {

    EditorObject() : gameObject(0), editorObject(0) {}

    GameObject* gameObject;
    GameObject* editorObject;
};