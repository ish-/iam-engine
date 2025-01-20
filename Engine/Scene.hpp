#pragma once
#include "Object3D.hpp"

class Scene : public Object3D {
public:
  virtual ~Scene() = default;
  virtual bool load ();
  virtual bool unload ();

  virtual bool update() = 0;
  virtual void render();
  virtual void exit() = 0;
};
