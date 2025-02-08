#pragma once
#include "Engine/Game.hpp"

class MyGame : public Game {
public:
  MyGame ();

  virtual void init () override;

  void sayHello () {
    LOG("Hello from MyGame");
  }
};
