#include "../Engine/Engine.hpp"
#include "../Engine/Inputs/Inputs.hpp"
#include "../util/LOG.hpp"
#include "HWScene.hpp"
#include <memory>


int main () {
  // Inputs inputs = Inputs::get();
  // WContext ctx {inputs};
  Engine& engine = Engine::get();
  auto scene = std::make_shared<HWScene>();
  // Scene scene;

  LOG("Hello World!");
  // auto scene = std::make_shared<HWScene>();
  engine.init(scene);
  engine.run(scene);
  engine.exit();
  LOG("Exit!");
  return 0;
}