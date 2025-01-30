#include "../Engine/Engine.hpp"
#include "../Engine/Inputs/Inputs.hpp"
#include "../Engine/common/LOG.hpp"
#include "HWScene.hpp"
#include <memory>


int main () {
  // Inputs inputs = Inputs::get();
  // WContext ctx {inputs};
  Engine& engine = Engine::get();
  // Scene scene;

  LOG("Hello World!");
  // auto scene = std::make_shared<HWScene>();
  engine.init();
  engine.setNewScene<HWScene>();
  engine.run();
  engine.exit();
  LOG("Exit!");
  return 0;
}