#pragma once
#include "Geo.hpp"

class BoxGeo: public Geo {
public:
  SINGLETON_PTR(BoxGeo)

  glm::vec2 size = glm::vec2(0, 0);

  BoxGeo(float _size = 1.);
};
