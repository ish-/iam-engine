#pragma once

// class Engine;

class World {
public:
  // World(Engine& engine);

  // Engine& engine;

  virtual ~World() = default;

  virtual void init();
  virtual void update();
  virtual void render();
  virtual void exit();
};
