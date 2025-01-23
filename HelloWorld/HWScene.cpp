#include "HWScene.hpp"
#include <glm/vec3.hpp>
#include <cmath>
#include <memory>
#include "../Engine/Inputs/Inputs.hpp"
#include "../Engine/Camera.hpp"
#include "../Engine/Graphic/Window.hpp"
#include "../Engine/Light.hpp"
#include "../Engine/BoxGeo.hpp"
#include "../Engine/Mesh.hpp"
#include "../util/LOG.hpp"
#include "../util/math.hpp"
#include "../util/random.hpp"
#include "Cube.hpp"
#include "SDL3/SDL_keycode.h"
#include "glm/ext/vector_float3.hpp"
#include "../Engine/Engine.hpp"
#include "../Engine/MovementCtrl.hpp"
using namespace std;
using namespace glm;

HWScene::HWScene ()
    : inputs(Inputs::get()), renderer(Renderer::get()) {

}

bool HWScene::load () {
  Window& w = Window::get();

  movementCtrl = make_shared<MovementCtrl>();
  movementCtrl->inertia = 0.1;
  movementCtrl->angularInertia = 0.1;
  movementCtrl->drag = 2.9;
  movementCtrl->angularDrag = 2.6;

  // cameraOrigin = make_shared<Object3D>();
  camera = make_shared<Camera>(80, w.width / w.height, 0.1, 1000);
  camera->translate(vec3(0, 0, .5));
  cameraOrigin = camera;
  // cameraOrigin->attach(camera);

  // camera->setRotation(vec3(60, 0, 0)); doest work
  light = make_shared<Light>();
  light->setPosition(vec3(1, 2, 3));
  light->color = vec3(1,1,.7);

  boxGeo = make_shared<BoxGeo>();
  cube = make_shared<Cube>();
  cube->geo = boxGeo;
  children.push_back(cube);

  auto cube2 = cube->clone<Cube>();
  cube2->scale(vec3(900., .1, .1));
  cube2->setPosition(vec3(2, 0, 0));
  cube2->tint = vec3(1.,0.,0.);
  children.push_back(cube2);

  auto cube3 = cube->clone<Cube>();
  cube3->scale(30);
  // cube3->setPosition(vec3(0, 2, -2));
  cube3->tint = vec3(0.,1.,0.);
  children.push_back(cube3);

  for (uint i = 0; i < 100; i++) {
    auto _cube = cube->clone<Cube>();
    _cube->setPosition(vec3( rd::in(-15., 15.), rd::in(-15., 15.), rd::in(-15., 15.)));
    _cube->tint = vec3( rd::in(0, 1), rd::in(0, 1), rd::in(0, 1));
    children.push_back(_cube);
  }

  inputs.mouseLock(true);

  return true;
}

void HWScene::update (float dt) {
  Window& w = Window::get();

  if (inputs.btn[SDLK_F]) {
    w.setFullscreen(true);
  }

  float pan = Engine::getCtx().inputs.btn[SDLK_A] - inputs.btn[SDLK_D]; // left-right
  float tilt = inputs.btn[SDLK_Q] - inputs.btn[SDLK_E]; // up-down
  float dolly = inputs.btn[SDLK_W] - inputs.btn[SDLK_S]; // forward-back
  if (pan != 0 || tilt != 0 || dolly != 0) {
    vec3 move = -vec3(pan, tilt, dolly);
    movementCtrl->applyForce(cameraOrigin->getForward() * move * vec3(50.));
  }

  float pitch = inputs.mouseRel.y; // pitch
  float yaw = (1 - inputs.btn[SDLK_LSHIFT]) * inputs.mouseRel.x;  // yaw
  float roll = inputs.btn[SDLK_LSHIFT] * inputs.mouseRel.x; // roll
  if (pitch != 0 || yaw != 0 || roll != 0) {
    vec3 rotate = -vec3(pitch, yaw, roll);
    movementCtrl->applyTorque(rotate * vec3(10.));
  }
  movementCtrl->update(dt, cameraOrigin.get());


  // cameraOrigin->rotateLocal(-rotate * dt);
  // // cameraOrigin->rotateSlerp(-rotate * dt, .3f);
  // cameraOrigin->translateLocal(-move * dt);


  for (auto& child : children)
    child->update();

  for (auto& child : children) {
    if (auto mesh = dynamic_pointer_cast<Mesh>(child)) {
      renderer.render(camera, light, mesh);
      mesh->draw();
    }
  }
  Super::update(dt);
  // return true;
}
