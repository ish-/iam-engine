#pragma once
#include <memory>
#include <SDL3/SDL_video.h>
// #include "Camera.hpp"
// #include "Light.hpp"
// #include "Scene.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "../ACS/ASystem.hpp"
#include "../../util/Symbol.hpp"
#include "MeshComponent.hpp"
using namespace std;
using namespace glm;

class Camera;
class Light;
class MeshComponent;
class Shader;
class SDL_Window;
// class SDL_GLContext;

class Renderer : public ASystem<MeshComponent> {
public:
  static Renderer& get() {
    static Renderer instance;
    return instance;
  }

  virtual Symbol getASystemType () override {
      static Symbol symbol { "Renderer" };
      return symbol;
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
  void render(shared_ptr<Camera> camera, vector<shared_ptr<Light>> lights, shared_ptr<MeshComponent> mesh);
  void renderComponents(shared_ptr<Camera> camera, vector<shared_ptr<Light>> lights);

  // TODO: pass by ref
  void setMVP(shared_ptr<Shader> shader, const MVP& mvp);
  void setLight(shared_ptr<Shader> shader, vector<shared_ptr<Light>> lights);
  // void render(const Scene& _scene, const RenderSceneOpts& opts);

// utils
  // shared_ptr<class WireframeShader> wireframeShader;

// settings
  bool wireframes = false;
};
