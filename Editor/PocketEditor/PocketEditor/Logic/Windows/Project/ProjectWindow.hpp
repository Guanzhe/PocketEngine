//
//  ProjectWindow.hpp
//  PocketEditor
//
//  Created by Jeppe Nielsen on 05/04/16.
//  Copyright © 2016 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "BaseWindow.hpp"
#include "SelectableCollection.hpp"
#include "EditorObject.hpp"

class FilePath;
class FileSystemListener;

class ProjectWindow : public BaseWindow {
protected:
    void OnInitialize() override;
    void OnCreate() override;
    std::string Name() override;
    bool CreateBar() override;
private:
    void ScreenSizeChanged();
    
    struct ClickedNodeInfo {
        GameObject* fileObject;
        GameObject* guiNodeObject;
        FilePath* filePath;
    };
    
    void Clicked(TouchData d, ClickedNodeInfo nodeInfo);
    GameObject* fileRoot;
    GameObject* listBox;
    AppMenu popupMenu;
    ClickedNodeInfo selectedNode;
    FileSystemListener* fileSystemListener;
};