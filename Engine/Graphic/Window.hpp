#pragma once
#include <SDL3/SDL_video.h>
#include "../../util/LOG.hpp"

class Window {
public:
    static Window& get() {
        static Window instance;
        return instance;
    }

    Window () {
        LOG("Window created!");
    };

    SDL_Window* sdlWindow;
    void Init();
    void Close() const;
    int width { 640 };
    int height { 640 };
};
