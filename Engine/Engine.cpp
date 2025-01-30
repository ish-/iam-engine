#include "Engine.hpp"
#include <filesystem>
#include <glad/glad.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_timer.h>

#include "Engine.hpp"
#include "Graphics/WireframeShader.hpp"
#include "Inputs/Inputs.hpp"
#include "Graphics/Window.hpp"
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
// r

Engine::Engine()
  : time(Time::get()), window(Window::get()), renderer(Renderer::get()), inputs(Inputs::get()), gui(GUI::get()), physics(Physics::get()),
    ctx{Time::get(), Window::get(), Renderer::get(), Inputs::get(), GUI::get(), Physics::get()}
{
  std::filesystem::current_path(BIN_TO_BUILD_PATH);
  LOG("Current path", std::filesystem::current_path().c_str());
}

void Engine::init() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    LOG("SDL failed initialization. %s", SDL_GetError());
    // throw std::exception("Something Bad happened here");
    throw std::runtime_error("SDL failed initialization.");
  }

  window.Init("Hello World");
  // window.setFullscreeln(true);
  renderer.init(window.sdlWindow);

  gui.init(window.sdlWindow, renderer.context);

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
    SDL_PollEvent(&event);
    ImGui_ImplSDL3_ProcessEvent(&event);
    inputs.update(event);

    if (event.type == SDL_EVENT_QUIT) return;
    if (inputs.btnRel[SDLK_ESCAPE] > 0) return;
    if (inputs.btn[SDLK_LSHIFT] && inputs.btnRel[SDLK_P] > 0) pause = !pause;
    if (inputs.btnRel[SDLK_F] > 0) {
      window.toggleFullscreen();
      scene->camera->setRatio((float)window.width / (float)window.height);
    }

    if (inputs.btnRel[SDLK_GRAVE] > 0) inputs.mouseLock(Bool::TOGGLE);

    if (!pause) {  // stop GL redrawing
      // Start ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplSDL3_NewFrame();
      ImGui::NewFrame();

      glViewport(0, 0, window.width, window.height);
      glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

      renderer.setScene(scene);
      scene->update(time.dT);

      ImGui::Begin("iam-engine");
        ImGui::Text("Perf: %i ~ %ims",
          int(1. / time.frameDur),
          int(time.frameComputing * 1000.));
        ImGui::Checkbox("Wireframes", &renderer.wireframes);
        ImGui::Checkbox("Shading", &renderer.shading);
        ImGui::Checkbox("Collisions", &physics.drawDebug);
      ImGui::End();

      physics.dynamicsWorld->debugDrawWorld();
      renderer.setShader(WireframeShader::get());

      if (physics.drawDebug)
        renderer.render(physics.debugDrawer->mesh);

      scene->drawGui();

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      SDL_GL_SwapWindow(window.sdlWindow);

      if (auto err = glGetError())
        LOG("GL ERROR", err);
    }

    // physicsManager.update();
    // graphicsManager.update();
    // bool bExit = gameplayManager.update();

    // graphicsManager.clear();

    // gameplayManager.draw();

    // graphicsManager.display();

    // if (bExit)
    //   break;

    time.beforeDelay();
    if (time.frameDelay > 0)
      SDL_Delay(time.frameDelay * 1000);
    time.endFrame();
  }
}