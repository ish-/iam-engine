#pragma once

class Time;
class Inputs;
class Window;
class Renderer;
class GUI;

struct IEngine {
public:
  // virtual ~IEngine() = default;

  Time& time;
  Window& window;
  Renderer& renderer;
  Inputs& inputs;
  GUI& gui;
  void exit();
};
