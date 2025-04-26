#pragma once
#include <memory>
#include <SDL3/SDL_video.h>
// #include "Camera.hpp"
// #include "Light.hpp"
// #include "Scene.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "../ASystem.hpp"
#include "../common/Symbol.hpp"
// #include "MeshComp.hpp"

using namespace std;
using namespace glm;

class Camera;
class Light;
class MeshComp;
class Shader;
class SDL_Window;
// class SDL_GLContext;

class Renderer : public ASystem/*<MeshComp>*/ {
public:
  static Renderer& get() {
    static Renderer instance;
    return instance;
  }

  static shared_ptr<Renderer>& getPtr() {
    static shared_ptr<Renderer> ptr = shared_ptr<Renderer>(&Renderer::get(), [](Renderer*) {});
    return ptr;
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

  unordered_map<
    shared_ptr<class Geo>,
    vector<shared_ptr<class MeshComp>>
  > geoToMeshComps;

  void init (SDL_Window* sdlWindow);
  // void setScene(shared_ptr<Scene> scene);
  void render(shared_ptr<MeshComp> mesh,  bool instanced = false);
  void renderComps();

  virtual void update(const vector<weak_ptr<AComp>>& comps, const float& dt) override;

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

  void logGlParams()
  {
    GLenum params[] = {
        GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
        GL_MAX_CUBE_MAP_TEXTURE_SIZE,
        GL_MAX_DRAW_BUFFERS,
        GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
        GL_MAX_TEXTURE_IMAGE_UNITS,
        GL_MAX_TEXTURE_SIZE,
        GL_MAX_VARYING_FLOATS,
        GL_MAX_VERTEX_ATTRIBS,
        GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
        GL_MAX_VERTEX_UNIFORM_COMPONENTS,
        GL_MAX_VIEWPORT_DIMS,
        GL_STEREO,
    };
    const char* names[] = {
        "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
        "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
        "GL_MAX_DRAW_BUFFERS",
        "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
        "GL_MAX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_TEXTURE_SIZE",
        "GL_MAX_VARYING_FLOATS",
        "GL_MAX_VERTEX_ATTRIBS",
        "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
        "GL_MAX_VIEWPORT_DIMS",
        "GL_STEREO",
    };
    LOG("logGlParams", "-----------------------------");
    LOG("logGlParams", "GL Context Params:");
    // integers - only works if the order is 0-10 integer return types
    for (int i = 0; i < 10; i++)
    {
      int v = 0;
      glGetIntegerv(params[i], &v);
      LOG("logGlParams", names[i] ," " ,v);
    }
    // others
    int v[2];
    v[0] = v[1] = 0;
    glGetIntegerv(params[10], v);
    LOG("logGlParams", names[10] ," " ,v[0] ," " ,v[1]);
    unsigned char s = 0;
    glGetBooleanv(params[11], &s);
    LOG("logGlParams", names[11] ," " ,(unsigned int)s);
    LOG("logGlParams", "");
  };
};
