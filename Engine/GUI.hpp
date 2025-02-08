#pragma once
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <glad/glad.h>

class GUI {
public:
  static GUI& get() {
    static GUI instance;
    return instance;
  }
  // GUI ();

  void init(SDL_Window* window, SDL_GLContext* gl_context);

  void update (const SDL_Event& event);
  void beginFrame ();
  void endFrame ();
};
