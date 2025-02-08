#include "GUI.hpp"
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_opengl3.h"

void GUI::init(SDL_Window* window, SDL_GLContext* gl_context) {
  // Initialize ImGui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // Initialize backends
  ImGui_ImplSDL3_InitForOpenGL(window, *gl_context);
  ImGui_ImplOpenGL3_Init("#version 330");
}

void GUI::update (const SDL_Event& event) {
  ImGui_ImplSDL3_ProcessEvent(&event);
}

void GUI::beginFrame () {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();
}

void GUI::endFrame () {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}