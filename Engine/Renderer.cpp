#include <glad/glad.h>
#include <SDL3/SDL_video.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Transform.hpp"
#include "glm/exponential.hpp"

using namespace glm;

void Renderer::init (SDL_Window* sdlWindow) {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

  SDL_GLContext context = SDL_GL_CreateContext(sdlWindow);
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

void Renderer::render (shared_ptr<Camera> camera, shared_ptr<Light> light, shared_ptr<Mesh> mesh) {
  GLuint shId = mesh->shader->shaderId;

  mat4 model = mesh->getAbsTransformMatrix();
  mat4 cameraMat = camera->getAbsTransformMatrix();
  mat4 view = glm::inverse(cameraMat);
  // mat4 normalMat = glm::inverseTranspose(modelView);

  glUseProgram(shId);
  // glUniformMatrix4fv(glGetUniformLocation(shId, "model"), 1, GL_FALSE, value_ptr(model));
  mesh->shader->setUniform("model", model);
  mesh->shader->setUniform("view", view);
  mesh->shader->setUniform("projection", camera->projection);

  mesh->shader->setUniform("lightPos", Transform(light->getAbsTransformMatrix()).getPosition());
  mesh->shader->setUniform("lightColor", light->color);
  mesh->shader->setUniform("lightAttenuationSq", light->atteniation * light->atteniation);
  mesh->shader->setUniform("viewPos", Transform(cameraMat).getPosition());
}
