#pragma once
#include "Geo.hpp"

class BoxGeo: public Geo {
public:
  static std::shared_ptr<BoxGeo> getPtr() {
    static std::shared_ptr<BoxGeo> instance = std::make_shared<BoxGeo>();
    return instance;
  }

  BoxGeo(float _size = 1.);
};