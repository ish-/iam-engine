#pragma once
#include <SDL3/SDL_video.h>
#include <glad/glad.h>
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_opengl3.h"

class GUI {
public:
  static GUI& get() {
    static GUI instance;
    return instance;
  }
  GUI ();

  void init(SDL_Window* window, SDL_GLContext* gl_context) {
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
};
