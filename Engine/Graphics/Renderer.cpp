#include <cstddef>
#include <glad/glad.h>
#include <stdexcept>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/exponential.hpp>

#include "Renderer.hpp"
#include "AComp.hpp"
#include "MeshComp.hpp"
#include "PhongShader.hpp"
#include "SDL3/SDL_video.h"
#include "Shader.hpp"
#include "../Camera.hpp"
#include "../Time.hpp"
#include "../Light.hpp"
#include "../Scene.hpp"
#include "WireframeShader.hpp"
#include "../Transform.hpp"
#include "glm/ext/quaternion_common.hpp"
#include <map>

using namespace glm;

#ifdef _WIN32
  // Enable dedicated graphics for NVIDIA:
  extern "C" { __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001; }
  // Enable dedicated graphics for AMD Radeon:
  extern "C" { __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1; }
#endif

void GLAPIENTRY GLDebugMessageCallback(GLenum Source,
    GLenum Type,
    GLuint Id,
    GLenum Severity,
    GLsizei Length,
    const GLchar* Message,
    const void* UserParam)
{
    static std::map<GLenum, const GLchar*> Sources =
    {
        {GL_DEBUG_SOURCE_API, "API"},
        {GL_DEBUG_SOURCE_WINDOW_SYSTEM, "WINDOW_SYSTEM"},
        {GL_DEBUG_SOURCE_SHADER_COMPILER, "SHADER_COMPILER"},
        {GL_DEBUG_SOURCE_THIRD_PARTY, "THIRD_PARTY"},
        {GL_DEBUG_SOURCE_APPLICATION, "APPLICATION"},
        {GL_DEBUG_SOURCE_OTHER, "OTHER"}
    };

    static std::map<GLenum, const GLchar*> Severities =
    {
        {GL_DEBUG_SEVERITY_HIGH, "HIGH"},
        {GL_DEBUG_SEVERITY_MEDIUM, "MEDIUM"},
        {GL_DEBUG_SEVERITY_LOW, "LOW"},
        {GL_DEBUG_SEVERITY_NOTIFICATION, "NOTIFICATION"}
    };

    static std::map<GLenum, const GLchar*> Types =
    {
        {GL_DEBUG_TYPE_ERROR, "ERROR"},
        {GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, "DEPRECATED_BEHAVIOR"},
        {GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, "UNDEFINED_BEHAVIOR"},
        {GL_DEBUG_TYPE_PORTABILITY, "PORTABILITY"},
        {GL_DEBUG_TYPE_PERFORMANCE, "PERFORMANCE"},
        {GL_DEBUG_TYPE_MARKER, "MARKER"},
        {GL_DEBUG_TYPE_PUSH_GROUP, "PUSH_GROUP"},
        {GL_DEBUG_TYPE_POP_GROUP, "POP_GROUP"},
        {GL_DEBUG_TYPE_OTHER, "OTHER"}
    };

    printf("[OpenGL %s] - SEVERITY: %s, SOURCE: %s, ID: %d: %s\n", Types[Type], Severities[Severity], Sources[Source], Id, Message);
}

void Renderer::init (SDL_Window* sdlWindow) {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
  // SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

  if (!SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8))
    LOG("SDL_GL_SetAttribute", SDL_GetError());

  SDL_GLContext _context = SDL_GL_CreateContext(sdlWindow);
  context = &_context;
  // gladLoadGLLoader(SDL_GL_GetProcAddress);
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    LOG("GLAD initialization FAILED");
    return;
  }

  // glEnable(GL_DEBUG_OUTPUT);
  // glDebugMessageCallback(GLDebugMessageCallback, 0);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  // TODO: enable culling
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClearDepthf(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  // deprecated
  // glEnable(GL_LINE_SMOOTH); glEnable(GL_POLYGON_SMOOTH); glEnable(GL_POINT_SMOOTH);

  // glEnable(GL_MULTISAMPLE);
  // glEnable(GL_SAMPLE_SHADING);
  // glMinSampleShading(8);
  // if (auto err = glGetError())
  //   LOG("INIT GL ERROR: ", err);

  // glEnable(GL_CULL_FACE);
  // glCullFace(GL_BACK);

  defaultShader = PhongShader::getPtr();
  setShader(defaultShader);
}


void Renderer::update (const vector<weak_ptr<AComp>>& comps, const float& dt) {
  // LOG("Renderer::renderComps");
  setFrameData();

  // auto comps = getComps();
  for (auto& wComp : comps) {
    if (auto comp = wComp.lock()) {
      shared_ptr<MeshComp> meshComp = dynamic_pointer_cast<MeshComp>(comp);
      if (meshComp) {
        render(meshComp);
      }
    }
  }
}

void Renderer::render (shared_ptr<MeshComp> mesh) {

  if (!mesh->conf.visible)
    return;

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  setShader(mesh->shader ? mesh->shader : shader);
  mat4 model = mesh->getAbsTransformMatrix();
  bool toShade = shading && mesh->conf.shaded;
  bool toWireframe = wireframes || mesh->conf.wireframe;
  if (toShade || toWireframe)
    shader->setUniform("model", model);

  // if (auto err = glGetError()) LOG("GL ERROR: before shading", err);
  if (toShade) {
    // if (auto err = glGetError()) LOG("GL ERROR: model", err);
    // LOG("tint!!", mesh->conf.tint.x, mesh->conf.tint.y, mesh->conf.tint.z);
    shader->setUniform("tintColor", mesh->conf.tint);
    // if (auto err = glGetError()) LOG("GL ERROR: tintColor", err);
    shader->setUniform("wireframes", 0.f);
    shader->setUniform("normalsMult", mesh->conf.invertNormals ? -1.f : 1.f);
    // if (auto err = glGetError()) LOG("GL ERROR: wireframes", err);

    mesh->draw();
    // if (auto err = glGetError()) LOG("GL ERROR: draw", err);
  }

  if (toWireframe) {
    shader->setUniform("wireframes", 1.f);
    // if (auto err = glGetError()) LOG("GL ERROR: wireframes2", err);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // if (auto err = glGetError()) LOG("GL ERROR: glPolygonMode", err);

    mesh->draw();
    // if (auto err = glGetError()) LOG("GL ERROR: draw2", err);
  }
}

void Renderer::setShaderViewProjection(shared_ptr<Shader> shader) {
  // LOG("Renderer::setShaderViewProjection");
  shader->setUniform("view", frameCache.view);
  shader->setUniform("projection", frameCache.projection);
  shader->setUniform("viewPos", frameCache.viewPos);
}

// struct ShaderLight {
//   vec3 pos;
//   vec3 color;
//   vec2 attenuationSq;
// };
void Renderer::setShaderLight(shared_ptr<Shader> shader) {
  // LOG("Renderer::setShaderLight");
  size_t curIdx = 0;
  for (size_t i = 0; i < scene->lights.size(); i++) {
    auto& light = scene->lights[i];
    vec3 lightPos = Transform(scene->lights[i]->getAbsTransformMatrix()).getPosition();
    // vec3 toLight = lightPos - Transform(mesh->getAbsTransformMatrix()).getPosition();
    // if (length(toLight) > light->attenuation[1])
    //   continue;

    std::string base = "lights[" + std::to_string(curIdx) + "]";
    shader->setUniform((base+".pos").c_str(), lightPos);
    shader->setUniform((base+".color").c_str(), light->conf.color);
    shader->setUniform((base+".atten").c_str(), light->conf.attenuation * light->conf.attenuation);
    curIdx++;
  }
  shader->setUniform("lightsNum", (int)curIdx);
}

void Renderer::setScene (shared_ptr<Scene> scene) {
  this->scene = scene;
}

void Renderer::setDefaultShader () {
  setShader(defaultShader);
}

void Renderer::setShader (shared_ptr<Shader> _shader) {
  if (_shader != shader) {
    shader = _shader;
    glUseProgram(shader->shaderId);
  }
  if (shader->frame < frameCache.frame) {
    setShaderViewProjection(shader);
    setShaderLight(shader);
    shader->frame = frameCache.frame;
  }
}

void Renderer::setFrameData () {
  auto nowFrame = Time::get().frame;

  if (frameCache.frame < nowFrame) {
    mat4 cameraMat = scene->camera->getAbsTransformMatrix();
    frameCache = {
      .frame = nowFrame,
      .view = glm::inverse(cameraMat),
      .projection = scene->camera->projection,
      .viewPos = Transform(cameraMat).getPosition()
    };
  }

  // setShader(shader);
}