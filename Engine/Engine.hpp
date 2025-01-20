#pragma
#include <memory>
#include <SDL3/SDL_video.h>

#include "Inputs/Inputs.hpp"
#include "Graphic/Window.hpp"

class Inputs;

class Engine {
  // common
public:
  virtual ~Engine() = default;

  // WContext& ctx;

  void init ();
  void run();
  void exit();

  double deltaTime;
  double elapsedTime;

// this
  std::shared_ptr<Window> window;
  Inputs inputs;
};
