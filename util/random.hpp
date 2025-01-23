#pragma once
#include "math.hpp"
#include <cstdlib>


namespace rd {
  static float f () {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  }

  static float in (float min, float max) {
    return min + f() * (max - min);
  }
}