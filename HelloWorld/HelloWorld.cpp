#include "../Engine/WContext.hpp"
#include "../Engine/Engine.hpp"
#include "../util/LOG.hpp"

int main () {
  Engine engine;
  engine.init();
  LOG("Hello World!");
  engine.run();
  engine.exit();
  return 0;
}