#include <memory>
#include <vector>
#include "../Engine/Scene.hpp"
#include "../Engine/BoxGeo.hpp"
#include "../Engine/Renderer.hpp"

#include "Cube.hpp"
#include "HWObject.hpp"
using namespace std;

class Inputs;

class HWScene : public Scene {
public:
  using Super = Scene;

  HWScene();
  Inputs& inputs;
  Renderer& renderer;
  //  = Inputs::get();

  shared_ptr<Object3D> cameraOrigin;
  shared_ptr<Cube> cube;
  shared_ptr<BoxGeo> boxGeo;
  vector<shared_ptr<HWObject>> children;

  virtual bool load () override;
  virtual bool update () override;

  // ~HWScene() = default;
};
