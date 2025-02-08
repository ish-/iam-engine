#include "Game.hpp"
#include "Scene.hpp"

Game::Game () {}

void Game::update(float dt) {
  scene->update(dt);
}
