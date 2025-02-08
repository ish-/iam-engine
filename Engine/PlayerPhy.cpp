#include "PlayerPhy.hpp"
#include <memory>
#include <glm/vec3.hpp>
// #include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <SDL3/SDL_keycode.h>

#include "Physics/PhysicsComp.hpp"
#include "PlayerPhyCtrlComp.hpp"
#include "Camera.hpp"
using namespace std;
using namespace glm;

void PlayerPhy::init () {
  auto scene = getScene();
  name = "PlayerPhy";

  setPosition(conf.initialPos);

  if (!scene->camera) {
    auto camera = scene->newActor<Camera>(conf.cameraConf);
    camera->setActive();
    attach(camera);
  }

  auto posMat = getAbsTransformMatrix();

  PhysicsComp::Params createParams {
    .shapeType = "SPHERE_SHAPE",
    .pos = btVector3(posMat[3][0], posMat[3][1], posMat[3][2]),
    .mass = 1.,
    .damping = vec2(.3, .3),
    // .initialImpulse = btVector3(rd::in(-10,10), rd::in(-10,10), rd::in(-10,10)),
  };
  phyComp = scene->newComp<PhysicsComp>(shared_from_this(), createParams);

  ctrlComp = scene->newComp<PlayerPhyCtrlComp>(shared_from_this());
}