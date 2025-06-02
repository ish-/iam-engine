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

}

void MeshComp::draw() {
  glBindVertexArray(geo->VAO);

  if (material) {
    material->bind();
  }

  glDrawElements(GL_TRIANGLES, geo->vertexCount, GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
}

void MeshComp::update (const float& dt) {

}

void MeshComp::init() {
  if (geo)
    return;

  if (conf.path.length() > 0) {
    auto modelFull = AssetStore::get().loadModel(conf.path);
    geo = modelFull->geo;
    material = modelFull->material;
  }
  else
    geo = BoxGeo::getPtr();

  if (conf.autoInstancing)
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

#include <Engine.hpp>
MeshComp::~MeshComp () {
  if (conf.autoInstancing && geo) {
    geo->instancesCount--;
  }
}

bool MeshComp::shouldInstance () { return conf.autoInstancing && getInstancesNum() > 1; }
bool MeshComp::shouldCulled () { return shouldInstance() ? conf.instancingCulling : conf.culling; }

BoundingBox MeshComp::getBoundingBox() {
  BoundingBox bb;
  if (conf.culling == CullingMode::NONE) {
    return bb;
  }

  auto transform = getAbsTransformMatrix();
  // bad transform
  // bb.min = glm::vec4(geo->boundingBox.min, 1) * transform;
  // bb.max = glm::vec4(geo->boundingBox.max, 1) * transform;

  // just position
  if (conf.culling == CullingMode::SPHERE) {
    vec3 pos = Transform(transform).getPosition();
    bb.min = geo->boundingBox.min + pos;
    bb.max = geo->boundingBox.max + pos;
    bb.update();
    return bb;
  }

  if (conf.culling == CullingMode::BB) {
    auto& localBB = geo->boundingBox;
    bb.min = glm::vec3(FLT_MAX);
    bb.max = glm::vec3(-FLT_MAX);

    for (int x = 0; x <= 1; ++x) {
      for (int y = 0; y <= 1; ++y) {
        for (int z = 0; z <= 1; ++z) {
          glm::vec3 corner = glm::vec3(
            x ? localBB.max.x : localBB.min.x,
            y ? localBB.max.y : localBB.min.y,
            z ? localBB.max.z : localBB.min.z
          );
          glm::vec3 worldCorner = glm::vec3(transform * glm::vec4(corner, 1.0f));
          bb.min = glm::min(bb.min, worldCorner);
          bb.max = glm::max(bb.max, worldCorner);
        }
      }
    }
    bb.update();
    return bb;
  }
}

int MeshComp::getInstancesNum () const {
  return geo->instancesCount;
}