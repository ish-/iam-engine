#include "PlayerPhy.hpp"
#include <memory>
#include <glm/vec3.hpp>
// #include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <SDL3/SDL_keycode.h>

#include "Inputs/Inputs.hpp"
#include "Physics/PhysicsComp.hpp"
#include "HealthComp.hpp"
#include "PlayerPhyCtrlComp.hpp"
#include "GunComp.hpp"
#include "Projectile.hpp"
#include "Camera.hpp"
#include "Light.hpp"
using namespace std;
using namespace glm;

void PlayerPhy::init () {
  setName("PlayerPhy");
  setPosition(conf.initialPos);

  auto scene = getScene();

  if (!scene->camera) {
    auto camera = scene->newActor<Camera>(conf.cameraConf);
    camera->setActive();
    attach(camera);
  }

  auto light = scene.get()->newActor<Light>((Light::Conf){
    // .color = vec3(1., 1., .7),
    // .intensity = 1.,
    .attenuation = vec2(10, 30.),
  });
  attach(light);

  auto posMat = getAbsTransformMatrix();

  PhysicsComp::Params createParams {
    .shapeType = "SPHERE_SHAPE",
    .pos = btVector3(posMat[3][0], posMat[3][1], posMat[3][2]),
    .mass = 1.,
    .damping = vec2(.3, .3),
  // .group = PhysicsComp::PLAYER,
    // .initialImpulse = btVector3(rd::in(-10,10), rd::in(-10,10), rd::in(-10,10)),
  };
  phyComp = scene->newComp<PhysicsComp>(shared(), createParams);

  ctrlComp = scene->newComp<PlayerPhyCtrlComp>(shared());

  scene->newComp<HealthComp>(shared(), HealthComp::Conf{
    .regen = .03,
    .takeDamageCallback = [](const float& damage, sp<Actor> actor) {
      std::cout << "Player took " << damage << " damage" << endl;
    },
  });

  gunComp = scene->newComp<GunComp>(shared());

  scene->player = shared();
}

#include <imgui.h>
void PlayerPhy::update(const float &dt)
{
  if (Inputs::get().btnRel[SDLK_SPACE] > 0.)
    gunComp->shoot();

  Actor::update(dt);

  ImGui::SetNextWindowPos(ImVec2(20, 20));
  ImGui::SetNextWindowSize(ImVec2(200, 50));
  ImGui::Begin("HUD", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
  ImGui::Text("Health:");
  ImGui::ProgressBar(getComp<HealthComp>()->conf.health, ImVec2(180, 20));
  ImGui::End();
}
