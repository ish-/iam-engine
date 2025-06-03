#pragma once
#include "Graphics/BoundingBox.hpp"
#include "MeshComp.hpp"
#include "Geo.hpp"
#include "Material.hpp"

class InstancedMeshComp : public MeshComp {
public:
  static sp<InstancedMeshComp> create (const sp<MeshComp>& meshComp) {
    auto instancedMesh = make_shared<InstancedMeshComp>();
    instancedMesh->conf = meshComp->conf;
    instancedMesh->geo = meshComp->geo;
    instancedMesh->material = meshComp->material;
    return instancedMesh;
  }

  BoundingBox bb;

  vector<mat4> transforms;
  virtual void draw() override {
    glBindVertexArray(geo->VAO);
    // if (auto err = glGetError()) LOG("GL ERROR: glBindVertexArray", err);

    if (material) {
      material->bind();
    }

    // geo->bindInstancingBuffer(transforms);
    glDrawElementsInstanced(GL_TRIANGLES, geo->vertexCount, GL_UNSIGNED_INT, 0, getInstancesNum());
    // glDrawArraysInstanced(GL_TRIANGLES, 0, geo->vertexCount, geo->instancesCount);
    // if (auto err = glGetError()) LOG("GL ERROR: glDrawArraysInstanced", err);

    glBindVertexArray(0);
    // if (auto err = glGetError()) LOG("GL ERROR: glBindVertexArray(0)", err);
  }

  virtual bool shouldInstance () override { return false; }
  virtual void init() override {

  }

  virtual void addTransform(const mat4& transform) {
    transforms.push_back(transform);
    auto pos = glm::vec3(transform[3]);
    bb.extend(pos.x, pos.y, pos.z);
    geo->instancesCount += 1;
  }

  BoundingBox getBoundingBox() override {
    bb.update();
    bb.radius += geo->boundingBox.radius;
    // std::cout << bb.center << " " << bb.radius << std::endl;
    return bb;
  }

  int getInstancesNum () const override {
    return transforms.size();
  }

  ~InstancedMeshComp (){
    // TODO: dirty fix to avoid double deletion
    geo->instancesCount += 1;
  }
};
