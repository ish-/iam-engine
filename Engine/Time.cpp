#include <SDL3/SDL_timer.h>
#include <chrono>
#include "Time.hpp"

double Time::update () {
  auto chronoNow = std::chrono::system_clock::now();
  abs = std::chrono::system_clock::to_time_t(chronoNow);
  // abs = std::ctime(&chronoTime);

  // Convert to time_t (absolute time in seconds since epoch)
  double now = SDL_GetTicks() / 1000.;
  dT = now - eT;
  eT = now;
  return dT;
}

double Time::endFrame () {
  double now = SDL_GetTicks() / 1000.;
  frameDelay = 1. / rate - (now - eT);
  return frameDelay;
}