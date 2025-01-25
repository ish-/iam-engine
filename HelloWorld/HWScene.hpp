#include <memory>
#include <vector>
#include "../Engine/Scene.hpp"
#include "../Engine/Object3D.hpp"
#include "glm/fwd.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
using namespace std;
using namespace glm;

class Inputs;
class MovementCtrl;
class Physics;
class Renderer;
class Object3D;
class Cube;
class BoxGeo;
class AMaestro;
class AActor;

class HWScene : public Scene {
public:
  using Super = Scene;

  HWScene();
  Inputs& inputs;
  Renderer& renderer;
  Physics& physics;
  AMaestro& maestro;
  shared_ptr<MovementCtrl> movementCtrl;
  //  = Inputs::get();

  struct GuiParams {
    float slider = .5f;
    vec4 color = {1,0,0,1};
    vec3 vec3 = {1,0,0};
  };
  GuiParams params;

  bool showWireframe = false;
  shared_ptr<Object3D> cameraOrigin;
  shared_ptr<AActor> cube;
  shared_ptr<BoxGeo> boxGeo;
  vector<shared_ptr<Object3D>> children;

  virtual bool load () override;
  virtual void update (float dt) override;

  // ~HWScene() = default;

  void drawGui () override;
};
