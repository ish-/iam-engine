#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

using namespace glm;

void Renderer::render (shared_ptr<Camera> camera, shared_ptr<Light> light, shared_ptr<Mesh> mesh) {
  GLuint shId = mesh->shader->shaderId;
  mat4 view = camera->matrix;
  mat4 modelView = view * mesh->matrix;
  mat4 modelViewProjection = camera->projection * modelView;
  mat4 normalMat = inverseTranspose(modelView);

  glUseProgram(shId);
  glUniformMatrix4fv(glGetUniformLocation(shId, "model"), 1, GL_FALSE, value_ptr(mesh->matrix));
  glUniformMatrix4fv(glGetUniformLocation(shId, "view"), 1, GL_FALSE, value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(shId, "projection"), 1, GL_FALSE, value_ptr(camera->projection));
  glUniformMatrix4fv(glGetUniformLocation(shId, "modelView"), 1, GL_FALSE, value_ptr(modelView));
  glUniformMatrix4fv(glGetUniformLocation(shId, "modelViewProjection"), 1, GL_FALSE,
                     value_ptr(modelViewProjection));
  glUniformMatrix4fv(glGetUniformLocation(shId, "normalMat"), 1, GL_FALSE, value_ptr(normalMat));
  glUniform3fv(glGetUniformLocation(shId, "lightPos"), 1, value_ptr(light->matrix));
}