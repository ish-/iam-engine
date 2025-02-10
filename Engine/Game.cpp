#include "Game.hpp"
#include "Scene.hpp"

Game::Game () {}

void Game::update (const float& dt) {
  scene->update(dt);
}
