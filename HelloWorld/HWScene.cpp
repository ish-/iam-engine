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
#include "../Engine/Graphics/Mesh.hpp"
#include "../Engine/Graphics/MeshComponent.hpp"
#include "../Engine/Graphics/PhongShader.hpp"
#include "../Engine/Physics/Physics.hpp"
#include "../Engine/GUI.hpp"
#include "../util/LOG.hpp"
#include "../util/math.hpp"
#include "../util/random.hpp"
#include "ACube.hpp"
#include "HWPlayer.hpp"
#include "SDL3/SDL_keycode.h"
#include "glm/ext/vector_float3.hpp"
#include "../Engine/Engine.hpp"
#include "../Engine/MovementCtrl.hpp"
#include "imgui.h"
#include "../Engine/Graphics/Renderer.hpp"
#include "../Engine/Time.hpp"
#include "../Engine/ACS/AMaestro.hpp"

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
  rd::globalSeed(time.abs);
}

bool HWScene::load () {
  Window& w = Window::get();
  physics.init();

  // movementCtrl = make_shared<MovementCtrl>();
  // movementCtrl->inertia = 0.1;
  // movementCtrl->angularInertia = 0.1;
  // movementCtrl->drag = 2.9;
  // movementCtrl->angularDrag = 2.6;

  shared_ptr<HWPlayer> player = maestro.newActor<HWPlayer>(vec3(0, 0, 5));

  camera = make_shared<Camera>((Camera::Conf){
    .ratio = (float)w.width / (float)w.height, .fov = 80.,
    .near = 0.1, .far = 1000 });
  player->attach(camera);

  light = make_shared<Light>(vec3(1, 2, 3), vec3(1, 1, .7));

  for (uint i = 0; i < 100; i++) {
    auto cube = maestro.newActor<ACube>(
      vec3( rd::in(-5., 5.), rd::in(-5., 5.), rd::in(-5., 5.))
    );
  }

  inputs.mouseLock(Bool::TRUE);

  return true;
}

void HWScene::update (float dt) {
  Window& w = Window::get();

  for(auto& actor : maestro.actors)
    actor->update();

  // float pan = Engine::getCtx().inputs.btn[SDLK_A] - inputs.btn[SDLK_D]; // left-right
  // float tilt = inputs.btn[SDLK_Q] - inputs.btn[SDLK_E]; // up-down
  // float dolly = inputs.btn[SDLK_W] - inputs.btn[SDLK_S]; // forward-back
  // if (pan != 0 || tilt != 0 || dolly != 0) {
  //   vec3 move = -vec3(pan, tilt, dolly);
  //   movementCtrl->applyForce(cameraOrigin->getForward() * move * vec3(50.));
  // }

  // if (bool mouseLocked = inputs.mouseLock(Bool::GET)) {
  //   float pitch = inputs.mouseRel.y; // pitch
  //   float yaw = (1 - inputs.btn[SDLK_LSHIFT]) * inputs.mouseRel.x;  // yaw
  //   float roll = inputs.btn[SDLK_LSHIFT] * inputs.mouseRel.x; // roll
  //   if (pitch != 0 || yaw != 0 || roll != 0) {
  //     vec3 rotate = -vec3(pitch, yaw, roll);
  //     movementCtrl->applyTorque(rotate * vec3(10.));
  //   }
  // }
  // movementCtrl->update(dt, cameraOrigin.get());

  physics.update(dt);
  renderer.renderComponents(camera, light);

  // for (auto& child : children)
  //   child->update();

  // // renderer.render(*this, { .wireframe = false });
  // for (auto& child : children) {
  //   if (auto mesh = dynamic_pointer_cast<Mesh>(child)) {
  //     mesh->wireframe = showWireframe;
  //     renderer.render(camera, light, mesh);
  //     mesh->draw();
  //   }
  // }

  // Super::update(dt);
}

void HWScene::drawGui () {
  ImGui::SliderFloat("Slider", &params.slider, 0.0f, 1.0f);
  ImGui::ColorEdit4("Color Picker", (float *)&params.color);
}