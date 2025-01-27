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

  struct FrameCache {
    unsigned int frame = 0;
    mat4 view;
    mat4 projection;
    vec3 viewPos;
  };
  // virtual ~Renderer() = default;
  // shared_ptr<Scene> scene;
  shared_ptr<class Shader> defaultShader;
  shared_ptr<class Shader> shader;
  shared_ptr<class Scene> scene;
  SDL_GLContext* context;
  FrameCache frameCache;

  void init (SDL_Window* sdlWindow);
  // void setScene(shared_ptr<Scene> scene);
  void render(shared_ptr<MeshComponent> mesh);
  void renderComponents();

  // TODO: pass by ref
  void setShaderViewProjection(shared_ptr<Shader> shader);
  void setShaderLight(shared_ptr<Shader> shader);
  // void render(const Scene& _scene, const RenderSceneOpts& opts);

  void setScene (shared_ptr<Scene> scene);
  void setShader (shared_ptr<class Shader> shader);
  void setDefaultShader ();
  void setFrameData ();

// utils
  // shared_ptr<class WireframeShader> wireframeShader;

// settings
  bool wireframes = false;
  bool shading = true;
};
