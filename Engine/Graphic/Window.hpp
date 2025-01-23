#pragma once
#include <SDL3/SDL_video.h>
#include "../../util/LOG.hpp"

class Window {
public:
    static Window& get() {
        static Window instance;
        return instance;
    }

    SDL_Window* sdlWindow;
    int width { 1280 };
    int height { 720 };

    void Init(const char* title);
    void Close() const;
    void setFullscreen(bool value);
};
