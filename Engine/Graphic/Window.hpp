#pragma once
#include <SDL3/SDL_video.h>

class Window {
public:
    SDL_Window* sdlWindow;
    void Init();
    void Close() const;
    int width { 640 };
    int height { 640 };
};
