//
//  IOSWindowCreator.h
//  PocketEngine
//
//  Created by Jeppe Nielsen on 3/10/13.
//  Copyright (c) 2013 Jeppe Nielsen. All rights reserved.
//

#pragma once
#include "Event.hpp"
#include "InputDevice.hpp"
#include <map>

namespace Pocket {
    class OSXWindowCreator {
      
    public:
        static OSXWindowCreator* Instance();
        
        void Create();
        
        int Width;
        int Height;
        bool FullScreen;
        
        Event<void*> OnInitialize;
        Event<bool> OnUpdate;
        Event<int, int> ScreenSizeChanged;
        
        void Down(int index, int x, int y);
        void Up(int index, int x, int y);
        void Move(int index, int x, int y);
        void Set(int index, int x, int y);
        
        void ButtonDown(const std::string& button, ModifierKey modifierKey);
        void ButtonUp(const std::string& button);
        void SetScroll(float delta);
        
        void* win;
        
    private:
        static OSXWindowCreator* instance;
        
        OSXWindowCreator();
        ~OSXWindowCreator();
        
        
        void KeyboardChanged(InputDevice::KeyboardEventData keyboardData);
        
        bool isKeyboardActive;
        
        InputDevice& inputDevice();
    };
}

