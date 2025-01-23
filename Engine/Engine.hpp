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
  void exit();

  void init(const std::shared_ptr<Scene>& scene);

  void run(const std::shared_ptr<Scene>& scene);


  bool pause = false;

// this
};
