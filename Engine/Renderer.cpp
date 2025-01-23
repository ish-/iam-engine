#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.hpp"
#include "Shader.hpp"

using namespace glm;

void Renderer::render (shared_ptr<Camera> camera, shared_ptr<Light> light, shared_ptr<Mesh> mesh) {
  GLuint shId = mesh->shader->shaderId;

  mat4 model = mesh->getAbsTransformMatrix();
  mat4 cameraMat = camera->getAbsTransformMatrix();
  mat4 view = glm::inverse(cameraMat);
  // mat4 normalMat = glm::inverseTranspose(modelView);

  glUseProgram(shId);
  glUniformMatrix4fv(glGetUniformLocation(shId, "model"), 1, GL_FALSE, value_ptr(model));
  glUniformMatrix4fv(glGetUniformLocation(shId, "view"), 1, GL_FALSE, value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(shId, "projection"), 1, GL_FALSE, value_ptr(camera->projection));

  glUniform3fv(glGetUniformLocation(shId, "lightPos"), 1, value_ptr(light->getAbsTransformMatrix()[3]));
  glUniform3fv(glGetUniformLocation(shId, "lightColor"), 1, value_ptr(light->color));
  glUniform2fv(glGetUniformLocation(shId, "lightAttenuation"), 1, value_ptr(light->atteniation));
  glUniform3fv(glGetUniformLocation(shId, "viewPos"), 1, value_ptr(cameraMat[3]));
}
