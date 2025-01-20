#pragma once
#include <memory>

class AActor;
class AComponent;

class AComponent : public std::enable_shared_from_this<AComponent> {
public:
    virtual ~AComponent() = default;

    void setOwner(const std::shared_ptr<AActor>& actor);

    std::shared_ptr<AActor> getOwner() const;

    virtual void update() = 0;

private:
    std::weak_ptr<AActor> owner;
};