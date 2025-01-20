#include "Engine.hpp"
#include "../util/LOG.hpp"
#include "SDL3/SDL_init.h"
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <glad/glad.h>

void Engine::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOG("SDL failed initialization. %s", SDL_GetError());
    // throw std::exception("Something Bad happened here");
    throw std::runtime_error("SDL failed initialization.");
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

  window = std::make_shared<Window>();
  window->Init();
  SDL_GLContext context = SDL_GL_CreateContext(window->sdlWindow);
  // gladLoadGLLoader(SDL_GL_GetProcAddress);
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    LOG("FAil");
    return;
    // throw(std::string("Failed to initialize GLAD"));
  }

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClearDepthf(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  window->Init();
}

void Engine::exit() {
  window->Close();
}

void Engine::run() {
  // gameplayManager.loadMap(startMap);
  SDL_Event event;

  while (true)
  {
    deltaTime = static_cast<double>(SDL_GetTicks()) / 1000.;
    LOG("run()", deltaTime);

    SDL_PollEvent(&event);
    // if (event.key.key == SDLK_ESCAPE)
    if (event.type == SDL_EVENT_QUIT)
      return;
    if (event.type == SDL_EVENT_KEY_DOWN) {
      if (event.key.key == SDLK_ESCAPE)
        return;
    }

    // inputManager.clear();

    // physicsManager.update();
    // graphicsManager.update();
    // bool bExit = gameplayManager.update();

    // graphicsManager.clear();

    // gameplayManager.draw();

    // graphicsManager.display();

    // if (bExit)
    //   break;
  }
}