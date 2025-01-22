#pragma once
#include <cstddef>
#include <memory>
#include <type_traits>
#include <SDL3/SDL_video.h>
// TODO: how move Scene to cpp?
#include "Scene.hpp"
#include "WContext.hpp"
#include "WObject.hpp"

class Inputs;
class Window;
class Renderer;
// class Scene;

class Engine {
  // common
public:
  // static Engine& get() {
  //   static Engine instance;
  //   return instance;
  // }
  Engine();

  // Engine(WContext& ctx) : ctx(ctx) {}
  virtual ~Engine() = default;

  // WContext& ctx;

  void init(const std::shared_ptr<Scene>& scene);

  void run(const std::shared_ptr<Scene>& scene);

  void exit();

  double deltaTime = 0;
  double elapsedTime = 0;
  bool pause = false;

// this
  std::shared_ptr<Window> window = nullptr;
  std::shared_ptr<Renderer> renderer = nullptr;
};
