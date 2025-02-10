#include "Actor.hpp"
#include <glm/gtx/quaternion.hpp>
#include "ACS/AComp.hpp"
#include "common/incrementTrailingDigits.hpp"

// Actor::Actor () {
//   name = getActorClassName();
// };

mat4 Actor::getAbsTransformMatrix() const {
  if (auto _parent = parent.lock()) {
      return _parent->getAbsTransformMatrix() * getTransformMatrix();
  }
  return getTransformMatrix();
}

void Actor::init () {
  // LOG("Actor::init()", getActorClassName(), "\"" + name + "\"");
}

void Actor::setName (std::string desiredName) {
  if (auto scene = getScene()) {
    if (auto existing = scene->getActorByName(desiredName))
      desiredName = incrementTrailingDigits(existing->name);
    name = desiredName;
    if (!name.empty())
      scene->actorsByName.erase(name);
    scene->actorsByName[desiredName] = shared_from_this();
  }
  else
    this->name = desiredName;
}

void Actor::attach(const std::shared_ptr<Actor>& child) {
  child->parent = shared_from_this();
  children.push_back(child);
}

std::shared_ptr<Actor> Actor::getParent() const {
  return parent.lock();
}

void Actor::update(const float& dt) {
  for (auto& [type, comp] : comps) {
    comp->update(dt);
  }
}

Actor::~Actor() {
  // LOG("~Actor()", name);
  comps.clear();
  children.clear();
}

bool Actor::removeComp(std::shared_ptr<AComp> comp) {
  // components[typeid(comp)] = nullptr;
  return true;
};
