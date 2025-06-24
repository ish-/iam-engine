#pragma once
#include "Engine/Scene.hpp"
#include "Graphics/PhongMaterial.hpp"

class DLScene2 : public Scene {
public:
  DLScene2 (const sp<class Game>& game) : Scene(game) {
    LOG("DLScene2 created");
  };

  sp<class PhongMaterial> asteroidMat;

  virtual void init () override;
  virtual void update (const float& dt) override;

  // virtual void drawGui () override;
};
