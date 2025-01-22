#pragma once
#include "HWObject.hpp"
#include "../Engine/Mesh.hpp"

class Cube : public HWObject, public Mesh {
public:
  Cube ();
  // ~Cube ();

  void update() override;
};
