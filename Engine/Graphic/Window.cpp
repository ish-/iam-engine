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
    LOG("w", w, "h", h);

    SDL_Rect displayBounds;
    SDL_GetDisplayBounds(1, &displayBounds);
    LOG("displayBounds 1", displayBounds.x, displayBounds.y, displayBounds.w, displayBounds.h);

    SDL_SetWindowSize(sdlWindow, displayBounds.w, displayBounds.h);
    SDL_SetWindowPosition(sdlWindow, displayBounds.x, displayBounds.y);
    SDL_SetWindowBordered(sdlWindow, false);
    width = displayBounds.w;
    height = displayBounds.w;

    // width = *w;
    // height = *h;
    // SDL_SetWindowFullscreen(sdlWindow, SDL_WINDOW_FULLSCREEN);
}

void Window::Close() const {
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}