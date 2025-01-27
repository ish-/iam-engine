#include <cstddef>
#include <glad/glad.h>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/exponential.hpp>

#include "Renderer.hpp"
#include "MeshComponent.hpp"
#include "PhongShader.hpp"
#include "Shader.hpp"
#include "../Camera.hpp"
#include "../Light.hpp"
#include "../Scene.hpp"
#include "WireframeShader.hpp"
#include "../Transform.hpp"

using namespace glm;

void Renderer::init (SDL_Window* sdlWindow) {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

  SDL_GLContext _context = SDL_GL_CreateContext(sdlWindow);
  context = &_context;
  // gladLoadGLLoader(SDL_GL_GetProcAddress);
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    LOG("GLAD initialization FAILED");
    return;
  }

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  // TODO: enable culling
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClearDepthf(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  // deprecated
  // glEnable(GL_LINE_SMOOTH); glEnable(GL_POLYGON_SMOOTH); glEnable(GL_POINT_SMOOTH);

  glEnable(GL_MULTISAMPLE);
  glMinSampleShading(8);
}


void Renderer::renderComponents (shared_ptr<Camera> camera, vector<shared_ptr<Light>> lights) {
  auto comps = getComponents();
  for (auto& comp : comps) {
    shared_ptr<MeshComponent> meshComp = dynamic_pointer_cast<MeshComponent>(comp);
    if (meshComp) {
      render(camera, lights, meshComp);
    }
  }
}

void Renderer::render (shared_ptr<Camera> camera, vector<shared_ptr<Light>> lights, shared_ptr<MeshComponent> mesh) {
  if (!mesh->visible)
    return;

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  mat4 cameraMat = camera->getAbsTransformMatrix();
  MVP mvp = {
    .model = mesh->getAbsTransformMatrix(),
    .view = glm::inverse(cameraMat),
    .projection = camera->projection,
    .viewPos = Transform(camera->getAbsTransformMatrix()).getPosition()
  };

  auto shader = mesh->shader;
  if (!shader)
    shader = PhongShader::getPtr();

  if (mesh->shaded) {
    glUseProgram(shader->shaderId);
    setMVP(shader, mvp);
    setLight(shader, lights, mesh);
    mesh->draw();
  }

  if (wireframes || mesh->wireframe) {
    shared_ptr<Shader> wfShader = WireframeShader::get();
    glUseProgram(wfShader->shaderId);
    setMVP(wfShader, mvp);
    // setUniform("wireColor", glm::vec3(1, 1, 1));
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    mesh->draw();
  }

  // shader->setUniform("wireColor", vec3(0,0,0));
}

void Renderer::setMVP(shared_ptr<Shader> shader, const MVP& mvp) {
  shader->setUniform("model", mvp.model);
  shader->setUniform("view", mvp.view);
  shader->setUniform("projection", mvp.projection);
  shader->setUniform("viewPos", mvp.viewPos);
}

// struct ShaderLight {
//   vec3 pos;
//   vec3 color;
//   vec2 atteniationSq;
// };
void Renderer::setLight(shared_ptr<Shader> shader, vector<shared_ptr<Light>> lights, shared_ptr<MeshComponent> mesh) {

  size_t curIdx = 0;
  for (size_t i = 0; i < lights.size(); i++) {
    auto& light = lights[i];
    vec3 lightPos = Transform(lights[i]->getAbsTransformMatrix()).getPosition();
    vec3 toLight = lightPos - Transform(mesh->getAbsTransformMatrix()).getPosition();
    if (length(toLight) > light->atteniation[1])
      continue;

    std::string base = "lights[" + std::to_string(curIdx) + "]";
    shader->setUniform((base+".pos").c_str(), lightPos);
    shader->setUniform((base+".color").c_str(), light->color);
    shader->setUniform((base+".atten").c_str(), light->atteniation * light->atteniation);
    curIdx++;
  }

  shader->setUniform("lightsNum", (int)curIdx);
}
