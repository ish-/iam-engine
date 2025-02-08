#pragma once
#include <memory>
#include <iostream>
#include "../common/Symbol.hpp"

#define ASYSTEM_TYPE(TYPE) \
  virtual Symbol getASystemType() override { static Symbol symbol{#TYPE}; return symbol; }

class Actor;

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

    void setOwner(const std::shared_ptr<Actor>& actor);

    std::shared_ptr<Actor> getOwner() const;

    virtual void update(float dt) {};

    ~AComp () {
        // std::cout << "~AComp\n";
    }

private:
    std::weak_ptr<Actor> owner;
};