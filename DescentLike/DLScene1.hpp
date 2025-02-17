#pragma once
#include "Engine/Scene.hpp"

class DLScene1 : public Scene {
public:
  DLScene1 (const sp<class Game>& game) : Scene(game) {
    LOG("DLScene1 created");
  };

  virtual void init () override;
  virtual void update (const float& dt) override;

  virtual void drawGui () override;
};
