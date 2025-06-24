#include "DLGame.hpp"
#include "DLScene2.hpp"
#include "Inputs/Inputs.hpp"

DLGame::DLGame (): Game() {}

void DLGame::init () {
  Game::init();
  // Inputs::get().mouseLock(Bool::TRUE);

  scene = newScene<DLScene2>();

  Inputs::get().mouseLock(Bool::TRUE);
}
