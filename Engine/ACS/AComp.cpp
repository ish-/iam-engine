#include "AComp.hpp"
// #include "common/LOG.hpp"

void AComp::setOwner(const std::shared_ptr<Object3D>& actor) {
    owner = actor;
}

std::shared_ptr<Object3D> AComp::getOwner() const {
    return owner.lock();
}