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

MeshComp::MeshComp(const Conf& conf): Mesh(conf), AComp() {

}



void MeshComp::update (const float& dt) {

}

void MeshComp::init() {
  Mesh::initMesh();
}

// TODO: cache it since it's not update()d
mat4 MeshComp::getAbsTransformMatrix() const {
  if (auto _parent = getOwner()) {
      return _parent->getAbsTransformMatrix() * getTransformMatrix();
  }
  return getTransformMatrix();
}

MeshComp::~MeshComp () {
  if (conf.autoInstancing && geo) {
    geo->instancesCount--;
  }
}
