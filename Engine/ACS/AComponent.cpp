#include "AComponent.hpp"
// #include "common/LOG.hpp"

void AComponent::setOwner(const std::shared_ptr<Object3D>& actor) {
    owner = actor;
}

std::shared_ptr<Object3D> AComponent::getOwner() const {
    return owner.lock();
}