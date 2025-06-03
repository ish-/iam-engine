#pragma once
#include "../AComp.hpp"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include "../Actor.hpp"
#include "../ILifecycle.hpp"
#include "AssetStore.hpp"

using namespace std;

class Symbol;
class Shader;
class Geo;

enum CullingMode {
  NONE = 0,
  SPHERE = 1,
  BB = 2,
};

class MeshComp : public AComp, public ILifecycle, public Transform {
public:
  virtual Symbol getASystemType () override;

  struct Conf {
    glm::vec3 tint = glm::vec3(1.);
    bool visible = true;
    bool shaded = true;
    bool wireframe = false;
    bool invertNormals = false;
    bool autoInstancing = true;
    bool instancingCulling = false;
    CullingMode culling = CullingMode::SPHERE;

    string path = "";

    JSON_DEFINE_OPTIONAL(Conf, tint, visible, shaded, wireframe, invertNormals, autoInstancing, path);
  };

  Conf conf;

  MeshComp(): AComp() {}
  MeshComp(const Conf& conf);

  shared_ptr<Geo> geo;
  sp<class Material> material;
  bool culled = false;

  virtual void draw();
  // virtual void drawInstances(const vector<mat4>& transforms);
  // virtual void drawInstances();

  virtual void init() override;

  void update (const float& dt) override;

  // TODO: cache it since it's not update()d
  mat4 getAbsTransformMatrix() const;

  virtual bool shouldInstance ();
  virtual bool shouldCulled ();
  virtual int getInstancesNum () const;

  virtual class BoundingBox getBoundingBox();

  ~MeshComp ();
};
