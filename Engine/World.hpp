#pragma once

class IWorld {
public:
  virtual ~IWorld() = default;

  virtual void update() = 0;
  virtual void render() = 0;
  virtual void exit() = 0;
};
