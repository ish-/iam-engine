#pragma once

class Time;
class Inputs;
class Window;
class Renderer;

struct IEngine {
public:
  // virtual ~IEngine() = default;

  Time& time;
  Window& window;
  Renderer& renderer;
  Inputs& inputs;
  void exit();
};
