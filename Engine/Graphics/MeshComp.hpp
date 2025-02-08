#pragma once
#include "../ACS/AComp.hpp"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include "../Actor.hpp"

using namespace std;

class Symbol;
class Shader;
class Geo;

class MeshComp : public AComp, public Actor {
public:
  shared_ptr<Shader> shader;
  shared_ptr<Geo> geo;

  MeshComp(): AComp() {}

  virtual Symbol getASystemType () override;

  glm::vec3 tint = glm::vec3(1.);
  bool visible = true;
  bool shaded = true;
  bool wireframe = false;
  string primitive = "BOX";

  JSON_DEFINE_OPTIONAL(MeshComp, tint, visible, shaded, wireframe);

  virtual void draw();

  virtual void init() override;

  void update (float dt) override;

  // TODO: cache it since it's not update()d
  mat4 getAbsTransformMatrix() const;
};
