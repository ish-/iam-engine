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
#include "glm/ext/vector_float3.hpp"
using namespace std;
using namespace glm;

HWScene::HWScene ()
    : inputs(Inputs::get()), renderer(Renderer::get()) {

}

bool HWScene::load () {
  Window& w = Window::get();

  cameraOrigin = make_shared<Object3D>();
  camera = make_shared<Camera>(80, w.width / w.height, 0.1, 1000);
  camera->translate(vec3(0, 0, 5));
  cameraOrigin->attach(camera);

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
    _cube->setPosition(vec3( rd::in(-10., 10.), rd::in(-10., 10.), rd::in(-10., 10.)));
    _cube->tint = vec3( rd::in(0, 1), rd::in(0, 1), rd::in(0, 1));
    children.push_back(_cube);
  }

  return true;
}

bool HWScene::update () {
  Window& w = Window::get();

  // cube->setRotation(vec3(inputs.mouse.x / 100, inputs.mouse.y / 100, 0));

  cameraOrigin->setRotation(vec3(
    remap(0.f, (float)w.width, -3.f, 3.f, inputs.mouse.y),
    remap(0.f, (float)w.height, -3.f, 3.f, inputs.mouse.x),
    0
  ));

  for (auto& child : children)
    child->update();

  for (auto& child : children) {
    if (auto mesh = dynamic_pointer_cast<Mesh>(child)) {
      renderer.render(camera, light, mesh);
      mesh->draw();
    }
  }
  Super::update();
  return true;
}
