#pragma once

struct IEngine {
public:
  // virtual ~IEngine() = default;

  class Time& time;
  class Window& window;
  class Renderer& renderer;
  class Inputs& inputs;
  class GUI& gui;
  class Physics& physics;

  void exit();
};
