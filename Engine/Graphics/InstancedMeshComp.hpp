#pragma once
#include "MeshComp.hpp"
#include "Geo.hpp"
#include "Material.hpp"

class InstancedMeshComp : public MeshComp {
public:
  static sp<InstancedMeshComp> create (const sp<MeshComp>& meshComp) {
    auto instancedMesh = make_shared<InstancedMeshComp>();
    instancedMesh->conf = meshComp->conf;
    instancedMesh->geo = meshComp->geo;
    instancedMesh->shader = meshComp->shader;
    instancedMesh->material = meshComp->material;
    return instancedMesh;
  }

  vector<mat4> transforms;
  virtual void draw() override {
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

  virtual void init() override {

  }
};
