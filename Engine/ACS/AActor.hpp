#pragma once
#include <iostream>
#include <memory>
#include <string>
// #include <vector>
#include <unordered_map>
#include <typeindex>
// #include "Object3D.hpp"
using namespace std;

class AComponent;
// class WContext;

class AActor {
public:
    template <typename T, typename... Args>
    static std::shared_ptr<T> create(Args&&... args) {
        auto actor = std::make_shared<T>(std::forward<Args>(args)...);
        actor->init();
        return actor;
    }

    string name = "noname";

    AActor() = default;
    AActor(const string& name): name(name) {
        std::cout << "AActor::AActor()\n";
    }

    std::unordered_map<std::type_index, std::shared_ptr<AComponent>> components;

    virtual void init();
    virtual void update();

    // template <typename T, typename... Args>
    // std::shared_ptr<T> addComponent(Args&&... args) {
    //     auto component = std::make_shared<T>(std::forward<Args>(args)...);
    //     try {
    //         component->setOwner(shared_from_this());
    //     } catch (const std::bad_weak_ptr& e) {
    //         std::cout << "AActor::addComponent() bad_weak_ptr\n";
    //         std::cout << "Do not try to addComponent() inside an initialization of the Actor\n";
    //     }
    //     components[typeid(T)] = component;
    //     return component;
    // }

    template <typename T>
    std::shared_ptr<T> getComponent() {
        auto it = components.find(typeid(T));
        if (it != components.end()) {
            return std::dynamic_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

};
