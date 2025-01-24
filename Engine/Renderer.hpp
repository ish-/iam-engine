#pragma once
#include <memory>
#include <SDL3/SDL_video.h>
// #include "Camera.hpp"
// #include "Light.hpp"
// #include "Scene.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
using namespace std;
using namespace glm;

class Camera;
class Light;
class Mesh;
class Shader;
class SDL_Window;
// class SDL_GLContext;

class Renderer {
public:
  static Renderer& get() {
    static Renderer instance;
    return instance;
  }

  struct RenderSceneOpts {
    bool wireframe = false;
  };
  struct MVP {
    mat4 model;
    mat4 view;
    mat4 projection;
    vec3 viewPos;
  };
  // virtual ~Renderer() = default;
  // shared_ptr<Scene> scene;
  SDL_GLContext* context;

  void init (SDL_Window* sdlWindow);
  // void setScene(shared_ptr<Scene> scene);
  void render(shared_ptr<Camera> camera, shared_ptr<Light> light, shared_ptr<Mesh> mesh);

  // TODO: pass by ref
  void setMVP(shared_ptr<Shader> shader, const MVP& mvp);
  void setLight(shared_ptr<Shader> shader, shared_ptr<Light> light);
  // void render(const Scene& _scene, const RenderSceneOpts& opts);
};
