#pragma once
#include "Graphics/MeshComp.hpp"
#include "Scene.hpp"
#include "Actor.hpp"

class MyScene : public Scene {
public:
  MyScene (const sp<Game>& game) : Scene(game) {
    LOG("MyScene created");
  };

  virtual void init () override;
  virtual void update(float dt) override;

  virtual void drawGui () override;
};
