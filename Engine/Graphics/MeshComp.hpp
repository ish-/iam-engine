#pragma once
#include "../ACS/AComp.hpp"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include "../Actor.hpp"
#include "../ILifecycle.hpp"
#include "MeshStorage.hpp"

using namespace std;

class Symbol;
class Shader;
class Geo;

class MeshComp : public AComp, public ILifecycle, public Transform {
public:
  virtual Symbol getASystemType () override;

  struct Conf {
    glm::vec3 tint = glm::vec3(1.);
    bool visible = true;
    bool shaded = true;
    bool wireframe = false;
    bool invertNormals = false;

    string path = "";

    JSON_DEFINE_OPTIONAL(Conf, tint, visible, shaded, wireframe, invertNormals, path);
  };

  Conf conf;

  MeshComp(): AComp() {}
  MeshComp(const Conf& conf): conf(conf), AComp() {
    if (conf.path.length() > 0)
      geo = MeshStorage::get().loadModel(conf.path);
  }

  shared_ptr<Shader> shader;
  shared_ptr<Geo> geo;

  virtual void draw();

  virtual void init() override;

  void update (const float& dt) override;

  // TODO: cache it since it's not update()d
  mat4 getAbsTransformMatrix() const;

  ~MeshComp () {
    // LOG("~MeshComp()");
  }
};
