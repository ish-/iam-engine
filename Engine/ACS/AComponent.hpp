#pragma once
#include <memory>
#include <iostream>

class Object3D;

// Base AComponent class
class AComponent : public std::enable_shared_from_this<AComponent> {
public:
    // virtual ~AComponent() = default;
    virtual ~AComponent() {
        std::cout << "AComponent::~AComponent()\n";
    };

    void setOwner(const std::shared_ptr<Object3D>& actor);

    std::shared_ptr<Object3D> getOwner() const;

    virtual void update(float dt) = 0;

private:
    std::weak_ptr<Object3D> owner;
};