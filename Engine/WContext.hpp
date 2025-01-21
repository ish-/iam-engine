#pragma once

class WCallbacks;
class WGraphics;
class WInputs;
class WPhysics;
class WTime;
class Engine;
class Scene;

struct WContext
{
  // WCallbacks &callbacks;

  // WGraphics &graphics;
  WInputs &inputs;
  Scene &scene;
  Engine &engine;
  // WPhysics &physics;
  WTime &time;
};
