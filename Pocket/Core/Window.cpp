#include "Window.hpp"

#ifdef IPHONE

#include "WindowiOS.hpp"

#elif OSX

#include "WindowOSX.hpp"

#elif EMSCRIPTEN

#include "WindowWeb.hpp"

#elif ANDROID

#include "WindowAndroid.hpp"

#else

#include "WindowWin.hpp"

#endif

using namespace Pocket;

Window::Window() {
    ResetDeltaTime = false;
}

Window::~Window() {
}

void Window::Create(int width, int height, bool fullScreen) {
}

bool Window::Update() {
	return false;
}

void Window::Destroy() {}
void Window::PreRender() {}
void Window::PostRender() {}

Window* Window::CreatePlatformWindow() {
#ifdef IPHONE
    return new WindowiOS();
#elif OSX
    return new WindowOSX();
#elif EMSCRIPTEN
    return new WindowWeb();
#elif ANDROID
    return new WindowAndroid();
#else
    return new WindowWin();
#endif
    
}

bool Window::Step() {
    bool exit = false;
    MainLoop(&exit);
    return exit;
}

void Window::Begin() {
    while (!Step()) {
        
    }
}

unsigned int Window::Framebuffer = 0;
