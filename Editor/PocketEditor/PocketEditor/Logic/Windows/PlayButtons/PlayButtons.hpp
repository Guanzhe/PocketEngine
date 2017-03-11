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
#include <map>

class PlayButtons : public BaseWindow {
protected:
    void OnInitialize() override;
    void OnCreate() override;
    std::string Name() override;
    bool CreateBar() override;
private:

    void ScreenSizeChanged();
    void ActiveWorldChanged(OpenWorld* old, OpenWorld* current) override;
    
    GameObject* editModePivot;
    GameObject* gameModePivot;
    
    void UpdateStates(OpenWorld* openWorld);
};
