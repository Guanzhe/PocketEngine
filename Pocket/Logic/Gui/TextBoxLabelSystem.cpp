//
//  TextBoxLabelSystem.h
//  GirlsNightOut
//
//  Created by Jeppe Nielsen on 8/31/14.
//  Copyright (c) 2014 Jeppe Nielsen. All rights reserved.
//

#include "TextBoxLabelSystem.hpp"
#include <cmath>

using namespace Pocket;

void TextBoxLabelSystem::Initialize(GameWorld* world) {
    this->world = world;
    cursor = 0;
    activeTextbox = 0;
    timer = 0;
    activeTextboxAdded = 0;
    activeTextboxAddedGO = 0;
}

void TextBoxLabelSystem::ObjectAdded(GameObject *object) {
    TextBox* textbox = object->GetComponent<TextBox>();
    textbox->Text.Changed.Bind(this, &TextBoxLabelSystem::TextBoxChanged, object);
    textbox->Active.Changed.Bind(this, &TextBoxLabelSystem::TextBoxChanged, object);
    if (textbox->Active) {
        activeTextboxAdded = textbox;
        activeTextboxAddedGO = object;
    }
    TextBoxChanged(object);
}

void TextBoxLabelSystem::ObjectRemoved(GameObject *object) {
    TextBox* textBox = object->GetComponent<TextBox>();
    textBox->Text.Changed.Unbind(this, &TextBoxLabelSystem::TextBoxChanged, object);
    textBox->Active.Changed.Unbind(this, &TextBoxLabelSystem::TextBoxChanged, object);
    if (cursor && activeTextbox == textBox) {
        cursor->Remove();
        cursor = 0;
    }
}

void TextBoxLabelSystem::TextBoxChanged(GameObject* object) {
    TextBox* textBox = object->GetComponent<TextBox>();
    object->GetComponent<Label>()->Text = textBox->Text;
    
    if (activeTextbox == textBox) {
        MoveCursor(textBox, object);
    }
}

void TextBoxLabelSystem::TextBoxActiveChanged(bool& active, GameObject *object) {
    
    TextBox* textBox = object->GetComponent<TextBox>();
    
    activeTextbox = 0;
    if (cursor) {
        cursor->Remove();
        cursor = 0;
    }
    
    if (textBox->Active) {
        activeTextbox = textBox;
        
        cursor = world->CreateObject();
        cursor->AddComponent<Transform>();
        cursor->Parent = object;
        cursor->AddComponent<Mesh>()->GetMesh<Vertex>().AddQuad(0, {cursorWidth,object->GetComponent<Label>()->FontSize * 1.1f}, Colour::Black());
        cursor->AddComponent<Material>();
        MoveCursor(textBox, object);
        
        timer = 0;
    }
}

void TextBoxLabelSystem::MoveCursor(Pocket::TextBox *textBox, GameObject *object) {
    if (!cursor) return;
    Mesh* mesh = object->GetComponent<Mesh>();
    if (mesh->Vertices().empty()) {
        Sizeable* sizeable = object->GetComponent<Sizeable>();
        cursor->GetComponent<Transform>()->Position = sizeable->Size * 0.5f;
    } else {
        const BoundingBox& bounds = mesh->LocalBoundingBox;
        Vector3 local = Vector3(bounds.center.x + bounds.extends.x * 0.5f + cursorWidth, bounds.center.y,0);
        cursor->GetComponent<Transform>()->Position = local;
    }
}

void TextBoxLabelSystem::Update(float dt) {
    
    if (activeTextboxAdded && activeTextboxAdded->Active) {
        TextBoxChanged(activeTextboxAddedGO);
        activeTextboxAdded = 0;
    }
    
    if (!cursor) return;
    timer += dt;
    
    //cursor->EnableComponent<Material>(fmodf(timer, 0.7f)<0.35f);
}
