#pragma once
#include "Geo.hpp"

class BoxGeo: public Geo {
public:
  static std::shared_ptr<BoxGeo> getPtr() {
    static std::shared_ptr<BoxGeo> instance = std::make_shared<BoxGeo>();
    return instance;
  }

  glm::vec2 size = glm::vec2(0, 0);

  BoxGeo(float _size = 1.);
};
