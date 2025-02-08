#pragma once

class ILifecycle {
public:
  virtual ~ILifecycle() = default;

  virtual void init() {};
  virtual void load() {};
  virtual void update(float dt) {};
  virtual void release() {};
};
