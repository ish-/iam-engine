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
  class AMaestro& maestro;

  // void exit();
};

class IHasCtx {
public:
  IHasCtx(IEngine& ctx) : _(ctx) {}

  IEngine& _;
};