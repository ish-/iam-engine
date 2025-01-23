#include "Inputs.hpp"
#include <SDL3/SDL_mouse.h>
#include "../Graphic/Window.hpp"
#include "../../util/LOG.hpp"

void Inputs::processMouse(const SDL_Event& event) {
  bool lb = event.button.button == SDL_BUTTON_LEFT;
  bool rb = event.button.button == SDL_BUTTON_RIGHT;
  float x = event.motion.x;
  float y = event.motion.y;

  mouseRel.lb = lb - mouse.lb;
  mouseRel.rb = rb - mouse.rb;
  mouseRel.x = event.motion.xrel;
  mouseRel.y = event.motion.yrel;

  mouse.lb = lb;
  mouse.rb = rb;
  mouse.x = x;
  mouse.y = y;
}

void Inputs::mouseLock(SDL_Window* sdlWindow, bool lock) {
  if (!SDL_SetWindowRelativeMouseMode(sdlWindow, lock))
    LOG("Cant lock cursor", SDL_GetError(), sdlWindow);
}
void Inputs::mouseLock(bool lock) {
   mouseLock(Window::get().sdlWindow, lock);
}