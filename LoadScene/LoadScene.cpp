#include "Engine/Engine.hpp"
#include "MyGame.hpp"

int main () {
  Engine& engine = Engine::get ();

  engine.init<MyGame>();
  engine.run();

  return 0;
}