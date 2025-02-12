#include "Inputs.hpp"
#include <SDL3/SDL_mouse.h>
// #include <objc/objc.h>
#include "../Graphics/Window.hpp"
#include "../common/LOG.hpp"
#include "SDL3/SDL_stdinc.h"

void Inputs::processMouse(const SDL_Event& event) {
  bool lb = event.button.button == SDL_BUTTON_LEFT;
  bool rb = event.button.button == SDL_BUTTON_RIGHT;
  float x = event.motion.x;
  float y = event.motion.y;

  mouseRel.lb = lb - mouse.lb;
  mouseRel.rb = rb - mouse.rb;
  mouseRel.x += event.motion.xrel;
  mouseRel.y += event.motion.yrel;

  mouse.lb = lb;
  mouse.rb = rb;
  mouse.x = x;
  mouse.y = y;

  auto w = Window::get();
  mouseNorm.x = x / w.width;
  mouseNorm.y = y / w.height;

  mouseClip.x = lerp(-1, 1, mouseNorm.x);
  mouseClip.y = lerp(-1, 1, mouseNorm.y);
}

bool Inputs::mouseLock(SDL_Window* sdlWindow, bool lock) {
  if (!SDL_SetWindowRelativeMouseMode(sdlWindow, lock)) {
    LOG("Cant lock cursor", SDL_GetError(), sdlWindow);
    return false;
  }
  // if (!(lock ? SDL_HideCursor() : SDL_ShowCursor())) {
  //   LOG("Cant lock cursor", SDL_GetError(), sdlWindow);
  //   return false;
  // }
  return true;
}

bool Inputs::mouseLock(Bool lock) {
  if (GET == lock)
    return mouseLocked;

  bool _lock = bool(lock);
  if (TOGGLE == lock)
    _lock = !mouseLocked;

  if (mouseLock(Window::get().sdlWindow, _lock))
    mouseLocked = _lock;
  return mouseLocked;
}
