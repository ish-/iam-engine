#include "AActor.hpp"
#include "AComponent.hpp"
#include "WContext.hpp"

AActor::AActor (WContext& ctx) : ctx(ctx) {

}

void AActor::update() {
  for (std::shared_ptr<AComponent>& component : components) {
    component->update();
  }
}

template <typename T, typename... Args>
std::shared_ptr<T> AActor::addComponent(Args&&... args) {
  auto component = std::make_shared<T>(std::forward<Args>(args)...);
  component->setOwner(this->shared_from_this());
  return component;
}