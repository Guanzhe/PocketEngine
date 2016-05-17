//
//  CompilationWindow.cpp
//  PocketEditor
//
//  Created by Jeppe Nielsen on 05/04/16.
//  Copyright © 2016 Jeppe Nielsen. All rights reserved.
//

#include "InspectorWindow.hpp"
#include "VirtualTreeListSystem.hpp"
#include "VirtualTreeListSpawnerSystem.hpp"
#include "EditorObject.hpp"
#include "FieldEditorSystem.hpp"
#include "GameObjectEditorSystem.hpp"
#include "SerializedFieldEditors.hpp"
#include "Project.hpp"

std::string InspectorWindow::Name() { return "Inspector"; }

void InspectorWindow::OnInitialize() {
    GameWorld& world = context->World();
    selectables = world.CreateSystem<SelectableCollection<EditorObject>>();
    selectables->SelectionChanged.Bind(this, &InspectorWindow::SelectionChanged);
    
    GameWorld& guiWorld = context->GuiWorld();
    
    guiWorld.CreateSystem<FieldEditorSystem>()->gui = &context->Gui();
    guiWorld.CreateSystem<GameObjectEditorSystem>()->gui = &context->Gui();
    
    guiWorld.CreateSystem<LayoutSystem>();
    
    CreateDefaultSerializedEditors();
}

void InspectorWindow::OnCreate() {

/*

    GameWorld& world = context->Project().World();
    GameObject* go = world.CreateObject();
 
    go->AddComponent<Transform>();
    go->AddComponent<Mesh>()->GetMesh<Vertex>().AddCube(0, {2,1,1});
    go->AddComponent<Material>();
    go->AddComponent<EditorObject>();
    go->AddComponent<Rotator>();

*/

    GameWorld& guiWorld = context->GuiWorld();
    Gui& gui = context->Gui();
    
    guiWorld.CreateSystem<FieldEditorSystem>()->gui = &gui;
    guiWorld.CreateSystem<GameObjectEditorSystem>()->gui = &gui;


    
    
   
    
    GameObject* pivot;
    GameObject* listBox = gui.CreateListbox(window, "Box", {0,0}, {200,400-50}, &pivot);
    listBox->RemoveComponent<Sprite>();
    
    gui.CreateControl(pivot, "Box", 100);
    
    
    
    inspectorEditor = gui.CreatePivot(pivot);
    inspectorEditor->AddComponent<Sizeable>()->Size = {200,400};
    inspectorEditor->AddComponent<GameObjectEditor>()->Object = 0;
}

void InspectorWindow::SelectionChanged(SelectableCollection<EditorObject> *selectables) {
    inspectorEditor->AddComponent<GameObjectEditor>()->Object = selectables->Selected().empty() ? 0 : selectables->Selected()[0];
}
