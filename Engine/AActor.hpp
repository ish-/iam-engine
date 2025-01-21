#pragma once
#include <memory>
#include <vector>
#include "Object3D.hpp"

class AComponent;
class WContext;

class AActor : public Object3D, public std::enable_shared_from_this<AActor> {
public:
    AActor(WContext& ctx);
    virtual ~AActor() = default;

    virtual void update();

    template <typename T, typename... Args>
    std::shared_ptr<T> addComponent(Args&&... args);

private:
    WContext& ctx;
    std::vector<std::shared_ptr<AComponent>> components;
};