#include <SDL3/SDL_timer.h>
#include <chrono>
#include "Time.hpp"
#include "common/LOG.hpp"

double Time::startFrame () {
  frame++;

  double now = SDL_GetTicks() / 1000.;
  // LOG("now, et", now, eT);
  dT = (now - eT);
  dT = dT > desiredFrameTime * 2. ? desiredFrameTime : dT;
  // updateMeanDelta(dT);
  eT += dT;
  return dT;
}

double Time::endFrame () {
  double now = SDL_GetTicks() / 1000.;
  frameDur = now - eT;
  return frameDur;
}

double Time::beforeDelay () {
  double now = SDL_GetTicks() / 1000.;
  frameComputing = now - eT;
  frameDelay = 1. / rate - frameComputing;
  return frameDelay;
}

long long Time::getSystemTime () {
  auto chronoNow = std::chrono::system_clock::now();
  return static_cast<long long>(std::chrono::system_clock::to_time_t(chronoNow));
}

// void Time::updateMeanDelta (const double& dT) {
//   meanDeltaBf[frame % 30] = dT;
//   meanDelta = 0;
//   for (int i = 0; i < 30; i++)
//     meanDelta += meanDeltaBf[i];
//   meanDelta /= 30;
// }