#pragma once
#include <vector>
#include <memory>
#include "AComponent.hpp"
#include "AMaestro.hpp"
#include "../../util/Symbol.hpp"
using namespace std;

// #define SINGLETON(classname) \
//   static classname& get() { \
//     static classname instance; \
//     return instance; \
//   }

template<typename AC = AComponent>
class ASystem {
public:
  static ASystem& get() {
    throw "ASystem::get() is only a copy-paste template";
    static ASystem instance;
    return instance;
  }

  virtual Symbol getASystemType () {
    static Symbol symbol { "<ASystem>" };
    return symbol;
  }

  vector<shared_ptr<AComponent>> getComponents () {
    static_assert(std::is_base_of<AComponent, AC>::value, "ASystem: AC must derive from AComponent");
    auto maestro = AMaestro::get();
    auto& allComps = maestro.components;
    auto sysType = getASystemType().name();
    auto& comps = allComps[getASystemType()];
    return comps;
    // return AMaestro::get().components[getASystemType()];
  }

  void update(const float& dt) {
    for (auto& component : getComponents()) {
      component->update(1000.);
    }
  }
};