#include <memory>
#include <vector>
#include "../Engine/Scene.hpp"
#include "Cube.hpp"
#include "HWObject.hpp"
using namespace std;

class Inputs;

class HWScene : public Scene {
public:
  using Super = Scene;

  HWScene();
  Inputs& inputs;
  //  = Inputs::get();

  shared_ptr<Cube> cube;
  vector<shared_ptr<HWObject>> children;

  virtual bool load () override;
  virtual bool update () override;

  // ~HWScene() = default;
};
