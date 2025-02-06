#pragma once
// #include "SDL3/SDL_mouse.h"
// #include "SDL3/SDL_oldnames.h"
// #include "SDL3/SDL_scancode.h"
#include "SDL3/SDL_keycode.h"
#include <SDL3/SDL_events.h>
#include <unordered_map>
#include <vector>

class SDL_Window;

enum Bool : uint8_t {
  FALSE = 0,
  TRUE = 1,
  TOGGLE = 2,
  GET = 3
};

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
  bool mouseLocked = false;
  MouseState mouseRel;

  void startFrame () {
    mouseRel = {0, 0, 0, 0};
    for (auto btnKey : lastBtnKeys)
      btnRel[btnKey] = 0;
  }

  bool update (SDL_Event& event) {
    SDL_Keycode& key = event.key.key;

    switch (event.type) {
      case SDL_EVENT_MOUSE_MOTION:
      case SDL_EVENT_MOUSE_BUTTON_DOWN:
        processMouse(event);
        break;

      case SDL_EVENT_KEY_DOWN:
        btnRel[key] = 1;
        btn[key] = true;
        lastBtnKeys.push_back(key);
        break;
      case SDL_EVENT_KEY_UP:
        btnRel[key] = -1;
        btn[key] = false;
        lastBtnKeys.push_back(key);
        break;
    }

    return false;
  }

  void processMouse (const SDL_Event& event);
  bool mouseLock(class SDL_Window* sdlWindow, bool lock);
  bool mouseLock(Bool lock);

  std::vector<SDL_Keycode> lastBtnKeys;
  std::unordered_map<SDL_Keycode, bool> btn;
  std::unordered_map<SDL_Keycode, int8_t> btnRel;
};
