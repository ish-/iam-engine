#pragma once
// #include "SDL3/SDL_mouse.h"
// #include "SDL3/SDL_oldnames.h"
// #include "SDL3/SDL_scancode.h"
#include "SDL3/SDL_keycode.h"
#include <SDL3/SDL_events.h>
#include <unordered_map>

class SDL_Window;

class MouseState {
public:
  float x = 0;
  float y = 0;
  bool lb = false;
  bool rb = false;
};

class Inputs {
public:
  static Inputs& get() {
    static Inputs instance;
    return instance;
  }

  MouseState mouse;
  MouseState mouseRel;

  bool update (SDL_Event& event) {
    mouseRel = {0, 0, 0, 0};
    SDL_Keycode& key = event.key.key;

    if (lastBtnKey != SDLK_UNKNOWN)
      btnRel[lastBtnKey] = 0;

    switch (event.type) {
      case SDL_EVENT_MOUSE_MOTION:
      case SDL_EVENT_MOUSE_BUTTON_DOWN:
        processMouse(event); break;

      case SDL_EVENT_KEY_DOWN:
        btnRel[key] = 1;
        btn[key] = true;
        lastBtnKey = key;
        break;
      case SDL_EVENT_KEY_UP:
        btnRel[key] = -1;
        btn[key] = false;
        lastBtnKey = key;
        break;
    }

    return false;
  }

  void processMouse (const SDL_Event& event);
  void mouseLock(class SDL_Window* sdlWindow, bool lock);
  void mouseLock(bool lock);

  SDL_Keycode lastBtnKey = SDLK_UNKNOWN;
  std::unordered_map<SDL_Keycode, bool> btn;
  std::unordered_map<SDL_Keycode, int8_t> btnRel;
};
