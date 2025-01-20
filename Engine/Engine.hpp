#pragma
#include <memory>
#include <SDL3/SDL_video.h>

#include "Graphic/Window.hpp"

class Engine {
  // common
public:
  virtual ~Engine() = default;

  // WContext& ctx;

  void init ();
  void run();
  void exit();

  double deltaTime;

// this
  std::shared_ptr<Window> window;
};
