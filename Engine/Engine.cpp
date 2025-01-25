#include "Engine.hpp"
#include <filesystem>
#include <glad/glad.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_timer.h>

#include "Engine.hpp"
#include "Inputs/Inputs.hpp"
#include "Graphics/Window.hpp"
#include "Graphics/Renderer.hpp"
#include "Physics/Physics.hpp"
#include "Time.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "GUI.hpp"
#include "../util/LOG.hpp"
#include "SDL3/SDL_opengl.h"
#include "IEngine.hpp"
// r

Engine::Engine()
  : ctx{Time::get(), Window::get(), Renderer::get(), Inputs::get(), GUI::get(), Physics::get()}
{
  std::filesystem::current_path(BIN_TO_BUILD_PATH);
  LOG("Current path: %s", std::filesystem::current_path().c_str());
}

void Engine::init(const std::shared_ptr<Scene>& scene) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    LOG("SDL failed initialization. %s", SDL_GetError());
    // throw std::exception("Something Bad happened here");
    throw std::runtime_error("SDL failed initialization.");
  }

  ctx.window.Init("Hello World");
  // ctx.window.setFullscreeln(true);
  ctx.renderer.init(ctx.window.sdlWindow);

  ctx.gui.init(ctx.window.sdlWindow, ctx.renderer.context);

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
    ctx.time.update();
    SDL_PollEvent(&event);
    ImGui_ImplSDL3_ProcessEvent(&event);
    ctx.inputs.update(event);

    if (event.type == SDL_EVENT_QUIT) return;
    if (ctx.inputs.btnRel[SDLK_ESCAPE] > 0) return;
    if (ctx.inputs.btnRel[SDLK_P] > 0) pause = !pause;
    if (ctx.inputs.btnRel[SDLK_F] > 0) {
      ctx.window.toggleFullscreen();
      scene->camera->update(80, (float)ctx.window.width / (float)ctx.window.height, 0.1, 1000);
    }

    if (ctx.inputs.btnRel[SDLK_TAB] > 0) {
      ctx.inputs.mouseLock(Bool::TOGGLE);
    }

    if (!pause) {  // stop GL redrawing
      // Start ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplSDL3_NewFrame();
      ImGui::NewFrame();

      glViewport(0, 0, ctx.window.width, ctx.window.height);
      glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


      scene->update(ctx.time.dT);

      ImGui::Begin("iam-engine");
        ImGui::Text("FPS: %i + %i", int(1. / ctx.time.dT), int(1. / ctx.time.frameDelay));
        ImGui::Checkbox("Engine pause (P)", &pause);
        ImGui::Checkbox("Wireframes", &ctx.renderer.wireframes);
      ImGui::End();

      scene->drawGui();

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

    ctx.time.endFrame();
    if (ctx.time.frameDelay > 0)
      SDL_Delay(ctx.time.frameDelay * 1000);
  }
}