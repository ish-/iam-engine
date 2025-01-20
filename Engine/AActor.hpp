#pragma once
#include <memory>
#include <vector>

class AComponent;
class WContext;

class AActor : public std::enable_shared_from_this<AActor> {
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