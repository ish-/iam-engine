#include "Engine.hpp"
#include <filesystem>
#include <glad/glad.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_timer.h>
#include "imgui.h"

#include "Engine.hpp"
#include "Graphics/WireframeShader.hpp"
#include "Inputs/Inputs.hpp"
#include "Graphics/Window.hpp"
#include "Graphics/Renderer.hpp"
// #include "ACS/AMaestro.hpp"
// #include "Graphics/WireframeShader.hpp"
#include "Physics/Physics.hpp"
#include "SDL3/SDL_keycode.h"
#include "Time.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "GUI.hpp"
#include "common/LOG.hpp"
#include "SDL3/SDL_opengl.h"
#include "IEngine.hpp"
// r

Engine::Engine()
  : time(Time::get()),
    window(Window::get()),
    renderer(Renderer::get()),
    inputs(Inputs::get()),
    gui(GUI::get()),
    physics(Physics::get())
    // ctx{Time::get(), Window::get(), Renderer::get(), Inputs::get(), GUI::get()}
{
  std::filesystem::current_path(BIN_TO_BUILD_PATH);
  LOG("Current path", std::filesystem::current_path().c_str());
}

void Engine::initSystems() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    LOG("SDL failed initialization. %s", SDL_GetError());
    // throw std::exception("Something Bad happened here");
    throw std::runtime_error("SDL failed initialization.");
  }

  window.Init("Hello World");
  // window.setFullscreeln(true);
  renderer.init(window.sdlWindow);

  gui.init(window.sdlWindow, renderer.context);
  // gui.init(ctx);

  if (auto err = glGetError()) {
    LOG("GL ERROR!", err); return; }
  // world = std::make_shared<World>(*this);
}


void Engine::exit() {
  window.Close();
}

void Engine::run() {
  // gameplayManager.loadMap(startMap);
  SDL_Event event;

  while (true)
  {
    time.startFrame();
    inputs.startFrame();
    while(SDL_PollEvent(&event)) {
      gui.update(event);
      inputs.update(event);
    }

    if (event.type == SDL_EVENT_QUIT) return;
    if (inputs.btnRel[SDLK_ESCAPE] > 0) return;
    if (inputs.btn[SDLK_LSHIFT] && inputs.btnRel[SDLK_P] > 0) pause = !pause;
    if (inputs.btn[SDLK_LCTRL] && inputs.btnRel[SDLK_R] > 0) game->init();
    if (inputs.btnRel[SDLK_F] > 0) {
      window.toggleFullscreen();
      // scene->camera->setRatio((float)window.width / (float)window.height);
    }

    if (inputs.btnRel[SDLK_GRAVE] > 0) inputs.mouseLock(Bool::TOGGLE);

    if (!pause) {  // stop GL redrawing
      // Start ImGui frame
      gui.beginFrame();

      glViewport(0, 0, window.width, window.height);
      glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

      renderer.setDefaultShader();
      game->update(time.dT);

      ImGui::Begin("iam-engine");
        ImGui::Text("Perf: %i ~ %ims",
          int(1. / time.frameDur),
          int(time.frameComputing * 1000.));
        ImGui::Checkbox("Wireframes", &renderer.wireframes);
        ImGui::Checkbox("Shading", &renderer.shading);
        ImGui::Checkbox("Collisions", &physics.drawDebug);
      ImGui::End();

      // ImGui::ShowDemoWindow();


      if (physics.drawDebug) {
        physics.debugDrawWorld();
        renderer.setShader(WireframeShader::get());
        renderer.render(physics.debugGetMesh());
      }

      // game->drawGui();

      gui.endFrame();
      SDL_GL_SwapWindow(window.sdlWindow);

      if (auto err = glGetError())
        LOG("GL ERROR", err);
    }

    time.beforeDelay();
    if (time.frameDelay > 0)
      SDL_Delay(time.frameDelay * 1000);
    time.endFrame();
  }
}