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
using namespace std;
using namespace glm;

HWScene::HWScene ()
    : inputs(Inputs::get()), renderer(Renderer::get()) {

}

bool HWScene::load () {
  Window& w = Window::get();

  cameraOrigin = make_shared<Object3D>();
  camera = make_shared<Camera>(80, w.width / w.height, 0.1, 100);
  camera->translate(vec3(0, 0, -5));
  cameraOrigin->attach(camera);

  // camera->setRotation(vec3(60, 0, 0)); doest work
  light = make_shared<Light>();

  boxGeo = make_shared<BoxGeo>();
  cube = make_shared<Cube>();
  cube->geo = boxGeo;
  children.push_back(cube);

  return true;
}

bool HWScene::update () {
  Window& w = Window::get();

  // cube->setRotation(vec3(inputs.mouse.x / 100, inputs.mouse.y / 100, 0));

  cameraOrigin->setRotation(vec3(
    remap(0.f, (float)w.width, -1.f, 1.f, inputs.mouse.x),
    remap(0.f, (float)w.height, -1.f, 1.f, inputs.mouse.y),
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
