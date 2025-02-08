#include "AComp.hpp"
// #include "common/LOG.hpp"

void AComp::setOwner(const std::shared_ptr<Actor>& actor) {
    owner = actor;
}

std::shared_ptr<Actor> AComp::getOwner() const {
    return owner.lock();
}