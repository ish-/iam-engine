#include <SDL3/SDL_timer.h>
#include <chrono>
#include "Time.hpp"

double Time::update () {
  frame++;

  double now = SDL_GetTicks() / 1000.;
  dT = now - eT;
  eT = now;
  return dT;
}

double Time::endFrame () {
  double now = SDL_GetTicks() / 1000.;
  frameDur = now - eT;
  frameDelay = 1. / rate - (now - eT);
  return frameDelay;
}