#pragma once
#include <memory>
#include <glm/vec3.hpp>
#include "Actor.hpp"
#include "Camera.hpp"
#include "common/json.hpp"

class PhysicsComp;
class PlayerPhyCtrlComp;
class GunComp;

class btRigidBody;
class btVector3;

class PlayerPhy : public Actor {
public:
  string getActorClassName() override { return "PlayerPhy"; }
  struct Conf {
    glm::vec3 initialPos = {0, 0, 5};
    Camera::Conf cameraConf = { .fov = 80 };

    JSON_DEFINE_OPTIONAL(Conf, initialPos);
  };
  Conf conf;

  PlayerPhy (): Actor() {};
  PlayerPhy (Conf& conf): conf(conf), Actor() {}

  std::shared_ptr<PhysicsComp> phyComp;
  std::shared_ptr<PlayerPhyCtrlComp> ctrlComp;
  std::shared_ptr<GunComp> gunComp;

  virtual void init() override;
  virtual void update(const float& dt) override;

  void shoot ();
};
