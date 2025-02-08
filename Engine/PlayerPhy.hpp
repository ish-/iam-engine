#pragma once
#include <memory>
#include <glm/vec3.hpp>
#include "Actor.hpp"
#include "Camera.hpp"

class PhysicsComp;
class PlayerPhyCtrlComp;
class btRigidBody;
class btVector3;

class PlayerPhy : public Actor {
public:
  struct Conf {
    glm::vec3 initialPos = {0, 0, 5};
    Camera::Conf cameraConf = { .fov = 80 };
  };
  Conf conf;

  PlayerPhy (): Actor() {};
  PlayerPhy (Conf& conf): conf(conf), Actor() {}

  std::shared_ptr<PhysicsComp> phyComp;
  std::shared_ptr<PlayerPhyCtrlComp> ctrlComp;

  virtual void init() override;
};
