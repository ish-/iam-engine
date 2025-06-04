#pragma once
#include "Transform.hpp"

class Geo;

enum CullingMode {
  NONE = 0,
  SPHERE = 1,
  BB = 2,
};

class Mesh : public Transform {
public:
  struct Conf {
    glm::vec3 tint = glm::vec3(1.);
    bool visible = true;
    bool shaded = true;
    bool wireframe = false;
    bool invertNormals = false;
    bool autoInstancing = true;
    bool instancingCulling = false;
    CullingMode culling = CullingMode::SPHERE;

    std::string path = "";

    JSON_DEFINE_OPTIONAL(Conf, tint, visible, shaded, wireframe, invertNormals, autoInstancing, path);
  };

  Mesh() = default;
  Mesh(const Conf& conf);

  Conf conf;

  wp<Mesh> parent;
  sp<Geo> geo;
  sp<class Material> material;
  bool culled = false;

  sp<Mesh> getParent() const { return parent.lock(); }
  virtual void draw();
  virtual void initMesh();

  // TODO: cache it since it's not update()d
  mat4 getAbsTransformMatrix() const;

  virtual bool shouldInstance ();
  virtual bool shouldCulled ();
  virtual int getInstancesNum () const;

  virtual class BoundingBox getBoundingBox();
};
