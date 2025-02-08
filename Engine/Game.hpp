#pragma once
#include "common/memory.hpp"
#include "ILifecycle.hpp"
#include "Scene.hpp"
using namespace std;

class Game : public ILifecycle, public std::enable_shared_from_this<Game> {
public:
  Game ();

  virtual void update(float dt) override;

  virtual void drawGui() {};

  template<typename SceneType = Scene>
  sp<Scene> newScene () {
    scene = std::make_shared<SceneType>(shared_from_this());
    scene->init();
    scene->load();
    return scene;
  }

  sp<Scene> scene;
};
