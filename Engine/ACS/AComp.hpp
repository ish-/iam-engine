#pragma once
#include <memory>
#include <iostream>
#include "../common/Symbol.hpp"

#define ASYSTEM_TYPE(TYPE) \
  virtual Symbol getASystemType() override { static Symbol symbol{#TYPE}; return symbol; }

class Object3D;

// Base AComp class
class AComp : public std::enable_shared_from_this<AComp> {
public:
    virtual Symbol getASystemType () {
        static Symbol symbol { "<ASystem>" };
        return symbol;
    }

    AComp () {
        // std::cout << "AComp()\n";
    }

    void setOwner(const std::shared_ptr<Object3D>& actor);

    std::shared_ptr<Object3D> getOwner() const;

    virtual void update(float dt) = 0;

    ~AComp () {
        // std::cout << "~AComp\n";
    }

private:
    std::weak_ptr<Object3D> owner;
};