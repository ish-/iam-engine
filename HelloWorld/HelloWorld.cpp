// #include "../Engine/WContext.hpp"
#include "../Engine/Engine.hpp"
// #include "../Engine/Scene.hpp"
#include "../util/LOG.hpp"
#include <memory>

int main () {
  Engine engine;
  // Scene scene;

  engine.init();
  LOG("Hello World!");
  auto scene = std::make_shared<Scene>();
  engine.run(scene);
  engine.exit();
  LOG("Exit!");
  return 0;
}