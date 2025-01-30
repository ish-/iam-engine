#pragma once
#include <cstddef>
#include <memory>
#include <type_traits>
#include <SDL3/SDL_video.h>
// TODO: how move Scene to cpp?
// #include "Scene.hpp"
#include "IEngine.hpp"

class Scene;

class Engine {
  // common
public:
  static Engine& get() {
    static Engine instance;
    return instance;
  }
  static IEngine& getCtx() {
    return Engine::get().ctx;
  }

  Engine();

  // Engine(WContext& ctx) : ctx(ctx) {}
  virtual ~Engine() = default;

  IEngine ctx;
  class Time& time;
  class Window& window;
  class Renderer& renderer;
  class Inputs& inputs;
  class GUI& gui;
  class Physics& physics;

  std::shared_ptr<Scene> scene;

  template <typename TScene = Scene>
  std::shared_ptr<TScene> newScene() {
    auto newScene = std::make_shared<TScene>();
    scene = newScene;
    return newScene;
  }

  void exit();

  void init();

  void run();

  bool pause = false;

// this
};
