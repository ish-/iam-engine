#include "AComponent.hpp"
// #include "../util/LOG.hpp"

void AComponent::setOwner(const std::shared_ptr<AActor>& actor) {
    owner = actor;
}

std::shared_ptr<AActor> AComponent::getOwner() const {
    return owner.lock();
}