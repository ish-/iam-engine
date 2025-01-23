#include "Inputs.hpp"

void Inputs::processMouse(const SDL_Event& event) {
  bool lb = event.button.button == SDL_BUTTON_LEFT;
  bool rb = event.button.button == SDL_BUTTON_RIGHT;
  float x = event.motion.x;
  float y = event.motion.y;

  mouseRel.lb = lb - mouse.lb;
  mouseRel.rb = rb - mouse.rb;
  mouseRel.x = event.motion.x - mouse.x;
  mouseRel.y = event.motion.y - mouse.y;

  mouse.lb = lb;
  mouse.rb = rb;
  mouse.x = x;
  mouse.y = y;
}