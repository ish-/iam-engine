#include "MyGame.hpp"
#include "MyScene.hpp"
#include "Inputs/Inputs.hpp"

MyGame::MyGame (): Game() {}

void MyGame::init () {
  Game::init();
  // Inputs::get().mouseLock(Bool::TRUE);

  scene = newScene<MyScene>();
}
