#include "../Engine/Scene.hpp"

class Inputs;

class HWScene : public Scene {
public:
  HWScene();
  Inputs& inputs;
  //  = Inputs::get();

  bool load () override;
  bool update () override;

  // ~HWScene() = default;
};
