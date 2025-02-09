#pragma once
#include "Engine/Scene.hpp"

class MyScene : public Scene {
public:
  MyScene (const sp<class Game>& game) : Scene(game) {
    LOG("MyScene created");
  };

  virtual void init () override;
  virtual void update(float dt) override;

  virtual void drawGui () override;
};
