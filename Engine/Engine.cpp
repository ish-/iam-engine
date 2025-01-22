#include "Engine.hpp"
#include <filesystem>
#include <glad/glad.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>

#include "Engine.hpp"
#include "Inputs/Inputs.hpp"
#include "Graphic/Window.hpp"
#include "Renderer.hpp"
#include "../util/LOG.hpp"
// r

Engine::Engine() : time(Time::get()) {
  std::filesystem::current_path(BIN_TO_BUILD_PATH);
  std::filesystem::path p = "resources/shaders/file.vert.glsl";
  LOG("Abs shaders fld", std::filesystem::absolute(p));
}

void Engine::init(const std::shared_ptr<Scene>& scene) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    LOG("SDL failed initialization. %s", SDL_GetError());
    // throw std::exception("Something Bad happened here");
    throw std::runtime_error("SDL failed initialization.");
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

  window = std::make_shared<Window>();
  renderer = std::make_shared<Renderer>();

  // auto cube = create<Mesh>();

  window->Init();
  SDL_GLContext context = SDL_GL_CreateContext(window->sdlWindow);
  // gladLoadGLLoader(SDL_GL_GetProcAddress);
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    LOG("GLAD initialization FAILED");
    return;
  }

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClearDepthf(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  scene->load();
  // world = std::make_shared<World>(*this);
}


void Engine::exit() {
  window->Close();
}


void Engine::run(const std::shared_ptr<Scene>& scene) {
  // gameplayManager.loadMap(startMap);
  SDL_Event event;

  Inputs* inputs = &Inputs::get();
  LOG("Inputs*", inputs);

  while (true)
  {
    SDL_PollEvent(&event);
    time.update();
    if (event.type == SDL_EVENT_QUIT)
      return;
    if (event.type == SDL_EVENT_KEY_DOWN)
      if (event.key.key == SDLK_ESCAPE)
        return;

    inputs->update(event);

    if (!pause) {  // stop GL redrawing
      glViewport(0, 0, window->width, window->height);
      glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

      scene->update();
      SDL_GL_SwapWindow(window->sdlWindow);
    }

    // physicsManager.update();
    // graphicsManager.update();
    // bool bExit = gameplayManager.update();

    // graphicsManager.clear();

    // gameplayManager.draw();

    // graphicsManager.display();

    // if (bExit)
    //   break;
    SDL_Delay(time.frameEnd());
  }
}