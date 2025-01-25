#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <typeindex>

#include "AActor.hpp"
#include "AComponent.hpp"

class AMaestro {
public:
  static AMaestro& get() {
    static AMaestro instance;
    return instance;
  }

  AMaestro() {}

  // vector<shared_ptr<AComponent>> components;
  unordered_map<std::type_index, vector<shared_ptr<AComponent>>> components;
  vector<shared_ptr<AActor>> actors;

  template <typename... Args>
  std::shared_ptr<AActor> newActor(Args&&... args) {
    auto actor = std::make_shared<AActor>(std::forward<Args>(args)...);
    actors.push_back(actor);
    actor->init();
    return actor;
  }

  template <typename T, typename... Args>
  std::shared_ptr<T> addComponent(shared_ptr<AActor> actor, Args&&... args) {
    auto component = std::make_shared<T>(std::forward<Args>(args)...);
    components[typeid(T)].push_back(component);
    actor->components[typeid(T)] = component;
    component->setOwner(actor);
    return component;
  }

  // template <typename T, typename... Args>
  // void removeComponent(shared_ptr<AActor> actor) {
  //   auto component = actor->components[typeid(T)];
  //   actor->components.erase(typeid(T));
  //   auto& sysComps = components[typeid(T)];
  //   sysComps.erase(std::remove(sysComps.begin(), sysComps.end(), component), sysComps.end());
  //   component->setOwner(nullptr);
  // }
};