#pragma once
#include <SDL3/SDL_video.h>

class Window {
public:
    static Window& get() {
        static Window instance;
        return instance;
    }

    Window () {};

    SDL_Window* sdlWindow;
    void Init();
    void Close() const;
    int width { 640 };
    int height { 640 };
};
