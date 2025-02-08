#include "MyGame.hpp"
#include "MyScene.hpp"

MyGame::MyGame (): Game() {}

void MyGame::init () {
  Game::init();
  scene = newScene<MyScene>();
}
