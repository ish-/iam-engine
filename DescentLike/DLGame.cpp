#include "DLGame.hpp"
#include "DLScene1.hpp"
#include "Inputs/Inputs.hpp"

DLGame::DLGame (): Game() {}

void DLGame::init () {
  Game::init();
  // Inputs::get().mouseLock(Bool::TRUE);

  scene = newScene<DLScene1>();

  Inputs::get().mouseLock(Bool::TRUE);
}
