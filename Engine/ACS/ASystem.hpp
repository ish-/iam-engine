#pragma once
#include <vector>
#include <memory>
#include "AComp.hpp"
#include "AMaestro.hpp"
#include "../common/Symbol.hpp"
using namespace std;

// #define SINGLETON(classname) \
//   static classname& get() { \
//     static classname instance; \
//     return instance; \
//   }

static const Symbol NO_SYSTEM { "<NO_SYSTEM>" };

template<typename AC = AComp>
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

  vector<weak_ptr<AComp>> getComps () {
    static_assert(std::is_base_of<AComp, AC>::value, "ASystem: AC must derive from AComp");
    auto maestro = AMaestro::get();
    auto& allComps = maestro.components;
    auto sysType = getASystemType().name();
    auto& comps = allComps[getASystemType()];
    return comps;
    // return AMaestro::get().components[getASystemType()];
  }

  void update(const float& dt) {
    for (auto& component : getComps()) {
      component->update(1000.);
    }
  }
};