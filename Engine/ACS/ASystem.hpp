#pragma once
// #include "AActor.hpp"
#include "AComponent.hpp"
#include "AMaestro.hpp"
#include <vector>
#include <memory>
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

  vector<shared_ptr<AComponent>> getComponents () {
    static_assert(std::is_base_of<AComponent, AC>::value, "ASystem: AC must derive from AComponent");
    return AMaestro::get().components[typeid(AC)];
  }

  void update() {
    for (auto& component : getComponents()) {
      component->update(1000.);
    }
  }
};