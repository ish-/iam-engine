#pragma once
#include <cmath>
#include <memory>
#include <vector>
#include <unordered_map>
#include <typeindex>

// #include "Actor.hpp"
#include "../Actor.hpp"
#include "../common/MACRO.hpp"
#include "../common/Symbol.hpp"
#include "../common/LOG.hpp"
#include "AComp.hpp"
using namespace std;

class AMaestro {
public:
  SINGLETON(AMaestro)

  AMaestro() {}

  // vector<shared_ptr<AComp>> components;
  unordered_map<Symbol, vector<weak_ptr<AComp>>> components;
  vector<shared_ptr<Actor>> actors;



  template <typename AA = Actor, typename... Args>
  std::shared_ptr<AA> newActor(Args&&... args) {
    // auto actor = std::make_shared<AA>(std::forward<Args>(args)...);
    // // actors.push_back(actor);
    // actor->init();
    // return actor;
  }

  template <typename T, typename... Args>
  std::shared_ptr<T> addComp(shared_ptr<Actor> actor, Args&&... args) {
    // auto component = std::make_shared<T>(std::forward<Args>(args)...);
    // auto sysType = component->getASystemType();
    // // LOG("Maestro::addComp", typeid(T).name(), "sysType", sysType.name());
    // component->setOwner(actor);
    // actor->comps[typeid(T)] = component;
    // components[sysType].push_back(component);
    // component->init();
    // return component;
  }
};