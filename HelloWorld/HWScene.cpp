#include "HWScene.hpp"
#include "../Engine/Inputs/Inputs.hpp"
#include "../util/LOG.hpp"

#include "../Engine/Camera.hpp"
#include "../Engine/Light.hpp"

HWScene::HWScene ()
    : inputs(Inputs::get()) {

}

bool HWScene::load () {
  camera = std::make_shared<Camera>(80, 1, 0.1, 100);
  light = std::make_shared<Light>();

  cube = std::make_shared<Cube>();
  children.push_back(cube);


  return true;
}

bool HWScene::update () {
  LOG("Mouse", inputs.mouse.x, inputs.mouse.y);
  for (auto& child : children) {
    child->update();
  }
  Super::update();
  return true;
}
