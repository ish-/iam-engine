#pragma once
#include <vector>
#include <memory>
#include "AComp.hpp"
// #include "AMaestro.hpp"
#include "../common/Symbol.hpp"
using namespace std;

// #define SINGLETON(classname) \
//   static classname& get() { \
//     static classname instance; \
//     return instance; \
//   }

static const Symbol NO_SYSTEM { "<NO_SYSTEM>" };

// template<typename AC = AComp>
class ASystem {
public:

  static ASystem& get() {
    throw "ASystem::get() is only a copy-paste template";
    static ASystem instance;
    return instance;
  }

  virtual Symbol getASystemType () {
    return NO_SYSTEM;
  }

  virtual void update(const vector<shared_ptr<AComp>>& comps, const float& dt) {
    // for (auto& comp : getComps()) {
    for (auto& comp : comps) {
      comp->update(dt);
    }
  }
};