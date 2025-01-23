#include "Engine.hpp"
#include <filesystem>
#include <glad/glad.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>

#include "Engine.hpp"
#include "Inputs/Inputs.hpp"
#include "Graphic/Window.hpp"
#include "Renderer.hpp"
#include "Time.hpp"
#include "Scene.hpp"
#include "../util/LOG.hpp"
#include "SDL3/SDL_opengl.h"
#include "IEngine.hpp"
// r

Engine::Engine()
  : ctx{Time::get(), Window::get(), Renderer::get(), Inputs::get()}
{
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

  ctx.window.Init();
  ctx.renderer.init(ctx.window.sdlWindow);

  // auto cube = create<Mesh>();



  if (auto err = glGetError())
    LOG("GL ERROR!", err);

  scene->load();
  // world = std::make_shared<World>(*this);
}


void Engine::exit() {
  ctx.window.Close();
}


void Engine::run(const std::shared_ptr<Scene>& scene) {
  // gameplayManager.loadMap(startMap);
  SDL_Event event;

  while (true)
  {
    SDL_PollEvent(&event);
    ctx.time.update();
    if (event.type == SDL_EVENT_QUIT)
      return;
    if (event.type == SDL_EVENT_KEY_DOWN)
      if (event.key.key == SDLK_ESCAPE)
        return;

    ctx.inputs.update(event);

    if (!pause) {  // stop GL redrawing
      glViewport(0, 0, ctx.window.width, ctx.window.height);
      glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

      scene->update(ctx.time.dT);
      SDL_GL_SwapWindow(ctx.window.sdlWindow);
    }

    // physicsManager.update();
    // graphicsManager.update();
    // bool bExit = gameplayManager.update();

    // graphicsManager.clear();

    // gameplayManager.draw();

    // graphicsManager.display();

    // if (bExit)
    //   break;
    SDL_Delay(ctx.time.frameEnd());
  }
}