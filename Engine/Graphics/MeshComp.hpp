#pragma once
#include "../AComp.hpp"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include "../Actor.hpp"
#include "../ILifecycle.hpp"
#include "AssetStore.hpp"
#include "Mesh.hpp"

using namespace std;

class Symbol;

class MeshComp : public AComp, public ILifecycle, public Mesh {
public:
  using Conf = Mesh::Conf;
  virtual Symbol getASystemType () override;

  MeshComp(): AComp() {}
  MeshComp(const Conf& conf);

  // virtual void drawInstances(const vector<mat4>& transforms);
  // virtual void drawInstances();

  vector<sp<Mesh>> children;

  mat4 getAbsTransformMatrix() const;

  virtual void init() override;

  void update (const float& dt) override;

  ~MeshComp ();
};
