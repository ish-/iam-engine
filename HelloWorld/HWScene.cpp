#include "HWScene.hpp"
#include <cstdio>
#include <glm/vec3.hpp>
#include <cmath>
#include <memory>
#include <string>
#include "../Engine/Inputs/Inputs.hpp"
#include "../Engine/Camera.hpp"
#include "../Engine/Graphics/Window.hpp"
#include "../Engine/Light.hpp"
#include "../Engine/Physics/Physics.hpp"
#include "../Engine/GUI.hpp"
#include "../util/LOG.hpp"
#include "../util/math.hpp"
#include "../util/random.hpp"
#include "ACube.hpp"
#include "HWPlayer.hpp"
#include "../Engine/Graphics/Renderer.hpp"
#include "../Engine/Time.hpp"
#include "../Engine/ACS/AMaestro.hpp"

#include "../Engine/Graphics/MeshModelComp.hpp"
#include "HWLevel.hpp"
#include "glm/fwd.hpp"
#include "imgui.h"

// TODO: tmp for debug

using namespace std;
using namespace glm;

HWScene::HWScene ()
    : inputs(Inputs::get()),
      renderer(Renderer::get()),
      physics(Physics::get()),
      maestro(AMaestro::get()),
      time(Time::get())
{
  auto globalTime = time.getSystemTime();
  LOG("Global Time", globalTime);
  rd::globalSeed(globalTime);
}

bool HWScene::load () {
  Window& w = Window::get();
  physics.init();

  shared_ptr<HWPlayer> player = maestro.newActor<HWPlayer>(vec3(0, 0, 5));

  camera = make_shared<Camera>((Camera::Conf){
    .ratio = (float)w.width / (float)w.height, .fov = 80.,
    .near = 0.1, .far = 1000 });
  player->attach(camera);

  lights.push_back(make_shared<Light>(vec3(0, 3.5, 1.5), vec3(1, 1, .7)));

  lights.push_back(make_shared<Light>(vec3(0.f, 0.f, 0.f), vec3(1.f, 1.f, .7f) / vec3(2.f), vec2(3.f, 8.f)));
  player->attach(lights.back());


  for (uint i = 0; i < 1000; i++) {
    auto cube = maestro.newActor<ACube>(
      vec3( rd::in(-20., 20.), rd::in(-20., 20.), rd::in(-20., 20.))
    );
  }

  // auto icosphere = maestro.newActor(vec3(2, 0, 0));
  // maestro.addComponent<MeshModelComp>(icosphere,
  //   (MeshModelComp::Conf){ .path = "resources/models/icosphere.s3.obj" });
  // PhysicsComponent::Params icospherePhysicsParams({
  //   .shape = new btSphereShape(.6),
  //   .pos = btVector3(2, 0, 0),
  // });
  // maestro.addComponent<PhysicsComponent>(icosphere, icospherePhysicsParams);

  // auto lvl = maestro.newActor<HWLevel>(vec3(10.f,0.f,0.f));
  // auto lvl = maestro.newActor(vec3(2, 0, 0));
  // maestro.addComponent<MeshModelComp>(lvl,
  //   (MeshModelComp::Conf){ .path = "resources/models/try_lvl.obj" });

  inputs.mouseLock(Bool::TRUE);

  return true;
}

void HWScene::update (float dt) {
  Window& w = Window::get();

  for(auto& actor : maestro.actors)
    actor->update();

  physics.update(dt);
  renderer.setDefaultShader();
  renderer.renderComponents();
}

void HWScene::drawGui () {
  ImGui::SliderFloat("Slider", &params.slider, 0.0f, 1.0f);
  ImGui::ColorEdit4("Color Picker", (float *)&params.color);

  // vec3 lightPos = light->getPosition();
  // ImGui::SliderFloat3("Light position", (float *)&lightPos, -10, 10);
  // light->setPosition(lightPos);
}