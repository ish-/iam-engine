#pragma once
#include <cmath>
#include <memory>
#include <vector>
#include <unordered_map>
#include <typeindex>

// #include "Object3D.hpp"
#include "../Object3D.hpp"
#include "../../util/MACRO.hpp"
#include "../../util/Symbol.hpp"
#include "AComponent.hpp"
using namespace std;

class AMaestro {
public:
  SINGLETON(AMaestro)

  AMaestro() {}

  // vector<shared_ptr<AComponent>> components;
  unordered_map<Symbol, vector<shared_ptr<AComponent>>> components;
  vector<shared_ptr<Object3D>> actors;

  template <typename AA = Object3D, typename... Args>
  std::shared_ptr<AA> newActor(Args&&... args) {
    auto actor = std::make_shared<AA>(std::forward<Args>(args)...);
    actors.push_back(actor);
    actor->init();
    return actor;
  }

  template <typename T, typename... Args>
  std::shared_ptr<T> addComponent(shared_ptr<Object3D> actor, Args&&... args) {
    auto component = std::make_shared<T>(std::forward<Args>(args)...);
    components[component->getASystemType()].push_back(component);
    component->setOwner(actor);
    return component;
  }

  // template <typename T, typename... Args>
  // void removeComponent(shared_ptr<Object3D> actor) {
  //   auto component = actor->components[typeid(T)];
  //   actor->components.erase(typeid(T));
  //   auto& sysComps = components[typeid(T)];
  //   sysComps.erase(std::remove(sysComps.begin(), sysComps.end(), component), sysComps.end());
  //   component->setOwner(nullptr);
  // }
};