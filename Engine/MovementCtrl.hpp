#pragma once
// TODO: glm deps
#include "Actor.hpp"
#include <glm/glm.hpp>
using namespace glm;

class MovementCtrl {
public:
    glm::vec3 position {0,0,0};
    glm::vec3 velocity {0,0,0};
    glm::vec3 appliedForce {0,0,0};

    glm::vec3 rotation {0,0,0};      // 3D rotation (pitch, yaw, roll)
    glm::vec3 angularVelocity {0,0,0};
    glm::vec3 appliedTorque {0,0,0};

    float mass = 1.0f;       // Mass of the object
    float drag = 0.1f;       // Drag coefficient
    float inertia = 0.9f;    // Inertia for velocity smoothing

    float angularDrag = 0.1f; // Angular drag coefficient
    float angularInertia = 0.9f; // Inertia for angular velocity smoothing

    // Apply a force to the object
    void applyForce(const glm::vec3& force) {
        appliedForce = glm::mix(appliedForce, force, 0.5f); // Smoothly apply the force
    }

    // Apply a torque to the object (rotational force)
    void applyTorque(const glm::vec3& torque) {
        appliedTorque = glm::mix(appliedTorque, torque, 0.5f); // Smoothly apply the torque
    }

    // Update the object's position and rotation based on the physics
    void update(float deltaTime, Actor* object) {
        // Compute acceleration
        glm::vec3 acceleration = appliedForce * (1.0f / mass);

        // Update velocity with inertia and drag
        velocity *= (1.0f - drag * deltaTime);
        velocity = glm::mix(velocity, velocity + acceleration * deltaTime, inertia);

        // object->translate(velocity * deltaTime); // Move the object

        // Reset the applied force
        appliedForce = glm::vec3(0.0f);

        // Compute angular acceleration
        glm::vec3 angularAcceleration = appliedTorque * (1.0f / mass);

        // Update angular velocity with inertia and angular drag
        angularVelocity *= (1.0f - angularDrag * deltaTime);
        angularVelocity = glm::mix(angularVelocity, angularVelocity + angularAcceleration * deltaTime, angularInertia);

        object->rotateLocal(angularVelocity * deltaTime); // Rotate the object
        object->translate(velocity * deltaTime); // Move the object

        // Reset the applied torque
        appliedTorque = glm::vec3(0.0f);
    }
};