#include "HWScene.hpp"
#include "../Engine/Inputs/Inputs.hpp"
#include "../util/LOG.hpp"

#include "../Engine/Camera.hpp"
#include "../Engine/Light.hpp"

HWScene::HWScene ()
    : inputs(Inputs::get()) {

  camera = std::make_shared<Camera>(80, 1, 0.1, 100);
  light = std::make_shared<Light>();
}

bool HWScene::load () {
  return true;
}

bool HWScene::update () {
  LOG("Mouse", inputs.mouse.x, inputs.mouse.y);
  return true;
}