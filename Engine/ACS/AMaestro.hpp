#pragma once
#include <cmath>
#include <memory>
#include <vector>
#include <unordered_map>
#include <typeindex>

// #include "Object3D.hpp"
#include "../Object3D.hpp"
#include "../common/MACRO.hpp"
#include "../common/Symbol.hpp"
#include "../common/LOG.hpp"
#include "AComponent.hpp"
using namespace std;

class AMaestro {
public:
  SINGLETON(AMaestro)

  AMaestro() {}

  // vector<shared_ptr<AComponent>> components;
  unordered_map<Symbol, vector<weak_ptr<AComponent>>> components;
  vector<shared_ptr<Object3D>> actors;

  template <typename AA = Object3D, typename... Args>
  std::shared_ptr<AA> newActor(Args&&... args) {
    auto actor = std::make_shared<AA>(std::forward<Args>(args)...);
    // actors.push_back(actor);
    actor->init();
    return actor;
  }

  template <typename T, typename... Args>
  std::shared_ptr<T> addComponent(shared_ptr<Object3D> actor, Args&&... args) {
    auto component = std::make_shared<T>(std::forward<Args>(args)...);
    auto sysType = component->getASystemType();
    // LOG("Maestro::addComponent", typeid(T).name(), "sysType", sysType.name());
    component->setOwner(actor);
    actor->components[typeid(component)] = component;
    components[sysType].push_back(component);
    return component;
  }
};