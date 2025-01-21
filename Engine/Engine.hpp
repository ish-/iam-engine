#pragma once
#include <memory>
#include <SDL3/SDL_video.h>
// TODO: how move Scene to cpp?
#include "Scene.hpp"

class Inputs;
class Window;
// class Scene;

class Engine {
  // common
public:
  virtual ~Engine() = default;

  // WContext& ctx;

  void init ();

  void run(std::shared_ptr<Scene>& scene);

  void exit();

  double deltaTime;
  double elapsedTime;
  bool pause;

// this
  std::shared_ptr<Window> window;
  std::shared_ptr<Inputs> inputs;
};
