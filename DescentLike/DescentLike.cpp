#include "Engine/Engine.hpp"
#include "DLGame.hpp"

int main () {
  Engine& engine = Engine::get();

  engine.init<DLGame>();
  engine.run();

  return 0;
}