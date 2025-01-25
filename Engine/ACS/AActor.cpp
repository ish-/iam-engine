#include <iostream>
#include "AActor.hpp"
#include "AComponent.hpp"

void AActor::update() {
  for (auto& [type, component] : components) {
    component->update(-1.);
  }
}

void AActor::init () {
  std::cout << "AActor::init ()\n";
}