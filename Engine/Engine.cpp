#include "Engine.hpp"
#include <filesystem>
#include <glad/glad.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_timer.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "imgui.h"

#include "Engine.hpp"
#include "Graphics/WireframeShader.hpp"
#include "Inputs/Inputs.hpp"
#include "Window.hpp"
#include "Graphics/Renderer.hpp"
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
#include "Game.hpp"
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
  LOG("Current path", std::filesystem::current_path().string());
  rd::globalSeed(time.getSystemTime());
}

void Engine::initSystems() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    LOG("SDL failed initialization. %s", SDL_GetError());
    // throw std::exception("Something Bad happened here");
    throw std::runtime_error("SDL failed initialization.");
  }

  window.Init("Window");
  // window.setFullscreeln(true);
  renderer.init(window.sdlWindow);

  gui.init(window.sdlWindow, renderer.context);
  // gui.init(ctx);

  if (auto err = glGetError()) {
    LOG("GL ERROR!", err); return; }
  // world = std::make_shared<World>(*this);

  game->init();
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
      game->scene->camera->setRatio((float)window.width / (float)window.height);
    }
    if (inputs.btnRel[SDLK_H] > 0) GUI::get().conf.showDebug = !GUI::get().conf.showDebug;

    if (inputs.btnRel[SDLK_GRAVE] > 0) inputs.mouseLock(Bool::TOGGLE);

    if (!pause) {  // stop GL redrawing
      // Start ImGui frame
      gui.beginFrame();

      glViewport(0, 0, window.width, window.height);
      glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

      renderer.setDefaultShader();
      game->update(time.dT);

      drawGui();

      if (physics.drawDebug) {
        physics.debugDrawWorld();
        renderer.setShader(WireframeShader::get());
        renderer.render(physics.debugGetMesh());
      }

      game->drawGui();

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

bool __imguiShowDemo = false;
void Engine::drawGui () {
  if (GUI::get().conf.showDebug) {
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::Begin("iam-engine");
      // ImGui::Checkbox("ImGgui Demo", &__imguiShowDemo);
      ImGui::Text("Perf: %i ~ %ims",
        int(1. / time.frameDur),
        int(time.frameComputing * 1000.));
      ImGui::Checkbox("Wireframes", &renderer.wireframes);
      ImGui::Checkbox("Shading", &renderer.shading);
      ImGui::Checkbox("Culling", &renderer.culling);
      ImGui::Checkbox("Auto Instacing", &renderer.autoInstancing);
      ImGui::Checkbox("Collisions", &physics.drawDebug);
      ImGui::SliderFloat("Sim Speed", &physics.conf.speed, 0.0, 10);
    ImGui::End();

    if (__imguiShowDemo) ImGui::ShowDemoWindow();
  }
}