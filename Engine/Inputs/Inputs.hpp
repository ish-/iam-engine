#pragma once
#include "SDL3/SDL_mouse.h"
// #include "SDL3/SDL_oldnames.h"
// #include "SDL3/SDL_scancode.h"
#include <SDL3/SDL_events.h>
#include <unordered_map>

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

  bool update (SDL_Event& event) {
    switch (event.type) {
      case SDL_EVENT_MOUSE_MOTION:
      case SDL_EVENT_MOUSE_BUTTON_DOWN:
        mouse.lb = event.button.button == SDL_BUTTON_LEFT;
        mouse.rb = event.button.button == SDL_BUTTON_RIGHT;
        mouse.x = event.motion.x;
        mouse.y = event.motion.y;
        break;

      case SDL_EVENT_KEY_DOWN:
        btn[event.key.key] = true;
        break;
      case SDL_EVENT_KEY_UP:
        btn[event.key.key] = false;
        break;
    }

    return false;
  }

  std::unordered_map<SDL_Keycode, bool> btn;
};
