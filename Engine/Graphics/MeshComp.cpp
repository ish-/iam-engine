#include "MeshComp.hpp"
#include <glad/glad.h>
#include "Graphics/PhongMaterial.hpp"
#include "Shader.hpp"
#include "Geo.hpp"
#include "BoxGeo.hpp"
#include "../common/Symbol.hpp"
#include "Material.hpp"
// #include <glm/vec3.hpp>
// using namespace glm;

Symbol MeshComp::getASystemType () {
  static Symbol symbol { "Renderer" };
  return symbol;
}

MeshComp::MeshComp(const Conf& conf): conf(conf), AComp() {
  if (conf.path.length() > 0) {
    geo = AssetStore::get().loadModel(conf.path);
  }
}

void MeshComp::draw() {
  glBindVertexArray(geo->VAO);

  if (material) {
    material->bind();
  }

  glDrawElements(GL_TRIANGLES, geo->vertexCount, GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
}

void MeshComp::drawInstances() {
  glBindVertexArray(geo->VAO);
  // if (auto err = glGetError()) LOG("GL ERROR: glBindVertexArray", err);

  if (material) {
    material->bind();
  }

  // geo->bindInstancingBuffer(transforms);
  glDrawElementsInstanced(GL_TRIANGLES, geo->vertexCount, GL_UNSIGNED_INT, 0, geo->instancesCount);
  // glDrawArraysInstanced(GL_TRIANGLES, 0, geo->vertexCount, geo->instancesCount);
  // if (auto err = glGetError()) LOG("GL ERROR: glDrawArraysInstanced", err);

  glBindVertexArray(0);
  // if (auto err = glGetError()) LOG("GL ERROR: glBindVertexArray(0)", err);
}

void MeshComp::update (const float& dt) {

}

void MeshComp::init() {
  if (geo)
    return;

  geo = BoxGeo::getPtr();
  geo->instancesCount++;

  material = PhongMaterial::getPtr();
}

// TODO: cache it since it's not update()d
mat4 MeshComp::getAbsTransformMatrix() const {
  if (auto _parent = getOwner()) {
      return _parent->getAbsTransformMatrix() * getTransformMatrix();
  }
  return getTransformMatrix();
}

MeshComp::~MeshComp () {
  geo->instancesCount--;
}

bool MeshComp::shouldInstance () { return conf.autoInstancing && geo->instancesCount > 1; }