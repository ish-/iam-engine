#pragma once
// #include "Actor.hpp"
#include <unordered_map>
#include <vector>
#include <functional>
#include <typeindex>
#include <nlohmann/json_fwd.hpp>
#include "common/memory.hpp"
#include "common/Symbol.hpp"
#include "common/LOG.hpp"
#include "ACS/ASystem.hpp"
#include "ILifecycle.hpp"
using namespace std;

class Light;
class Camera;
class Actor;
class Game;
class AComp;

class Physics;
class Renderer;

class Scene :  public ILifecycle, public std::enable_shared_from_this<Scene>  {
public:
  Scene (const wp<Game>& game) : game(game) {
    LOG("Scene created");
  };

  sp<Game> getGame () { return game.lock(); }
  wp<Game> game;
  sp<Physics> physics;
  sp<Renderer> renderer;

  sp<Camera> camera;
  vector<sp<Light>> lights;
  sp<Actor> player;

  template <typename ActorType = Actor, typename... Args>
  std::shared_ptr<ActorType> newActor(Args&&... args) {
    auto actor = std::make_shared<ActorType>(std::forward<Args>(args)...);
    actors.push_back(actor);
    actor->scene = shared_from_this();
    actor->init();
    return actor;
  }

  template <typename ActorType = Actor, typename... Args>
  std::shared_ptr<ActorType> addActor(const shared_ptr<ActorType>& actor) {
    actors.push_back(actor);
    actor->scene = shared_from_this();
    actor->init();
    return actor;
  }

  template <typename ACompType = AComp>
  std::shared_ptr<ACompType> addComp(const sp<Actor>& actor, const sp<ACompType>& comp) {
    auto sysType = comp->getASystemType();
    compsBySystem[sysType].push_back(comp);
    _addCompToActor(actor, typeid(ACompType), comp);
    comp->init();
    return comp;
  }

  template <typename ACompType = AComp, typename... Args>
  std::shared_ptr<ACompType> newComp(const sp<Actor>& actor, Args&&... args) {
    auto comp = std::make_shared<ACompType>(std::forward<Args>(args)...);
    return addComp<ACompType>(actor, comp);
  }

  void sayHello () {
    LOG("Hello from Scene");
  }

  void loadJson (string path);

  sp<Actor> getActorByName(string name) {
    auto it = actorsByName.find(name);
    if (it == actorsByName.end()) {
      LOG("getActorByName: Actor not found", name);
      return nullptr;
    }
    return it->second;
  }

  virtual void init() override;
  virtual void update(float dt) override;

  virtual void drawGui ();

  vector<sp<Actor>> actors{};
  unordered_map<string, sp<Actor>> actorsByName{};
  // TODO: remake to weak_ptr
  unordered_map<Symbol, vector<shared_ptr<AComp>>> compsBySystem;
  unordered_map<Symbol, weak_ptr<ASystem>> systems;
  void _addCompToActor (const sp<Actor>& actor, const type_index& typeId, const sp<AComp>& comp);

  // using ConstructorFunc = sp<Actor>(*)(class nlohmann::json);
  using ActorCtorFunc = std::function<sp<Actor>(const nlohmann::json&)>;
  unordered_map<string, ActorCtorFunc> actorCtors;

  using ACompCtorFunc = std::function<sp<AComp>(const sp<Actor>& actor, const nlohmann::json&)>;
  unordered_map<string, ACompCtorFunc> compCtors;
};
