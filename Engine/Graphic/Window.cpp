#include "Window.hpp"
#include "SDL3/SDL_video.h"

#include <SDL3/SDL_init.h>
#include <string>

using std::string;

void Window::Init(const char* title) {
    SDL_Init(SDL_INIT_VIDEO);

    sdlWindow = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
}

void Window::setFullscreen(bool value) {
    int w, h;
    SDL_GetWindowMaximumSize(sdlWindow, &w, &h);
    SDL_Rect displayBounds;
    SDL_GetDisplayBounds(1, &displayBounds);
    LOG("displayBounds 1", displayBounds.x, displayBounds.y, displayBounds.w, displayBounds.h);

    SDL_SetWindowBordered(sdlWindow, !value);
    SDL_SetWindowPosition(sdlWindow, displayBounds.x, displayBounds.y);
    if (value)
        SDL_SetWindowSize(sdlWindow, displayBounds.w, displayBounds.h);
    else
        SDL_SetWindowSize(sdlWindow, 1280, 800);
    width = displayBounds.w;
    height = displayBounds.h;
    fullscreen = value;
    // SDL_SetWindowFullscreen(sdlWindow, SDL_WINDOW_FULLSCREEN);
}
void Window::toggleFullscreen() {
    setFullscreen(!fullscreen);
}

void Window::Close() const {
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}