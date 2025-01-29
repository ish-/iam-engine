#include <btBulletDynamicsCommon.h>
#include <glad/glad.h> // Ensure GLAD or GLEW is properly initialized
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <vector>
#include <iostream>
#include "DebugDrawMeshComponent.hpp"

class DebugDrawer : public btIDebugDraw {
public:
    DebugDrawer() : debugMode(DBG_DrawWireframe) {

        // glGenVertexArrays(1, &vao);
        // glBindVertexArray(vao);

        // glGenBuffers(1, &vbo);
        // glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // glBufferData(GL_ARRAY_BUFFER, maxLines * sizeof(Line), nullptr, GL_DYNAMIC_DRAW);

        // glEnableVertexAttribArray(0);
        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Line), (void*)offsetof(Line, start));
        // glEnableVertexAttribArray(1);
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Line), (void*)offsetof(Line, end));
        mesh = std::make_shared<DebugDrawMeshComponent>();
    }

    std::shared_ptr<DebugDrawMeshComponent> mesh;

    void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override {
        mesh->lines.push_back(DebugDrawGeo::Line{ glm::vec3(from.x(), from.y(), from.z()) });
        mesh->lines.push_back(DebugDrawGeo::Line{ glm::vec3(to.x(), to.y(), to.z()) });
                            //   glm::vec3(color.x(), color.y(), color.z()) });
    }

    void drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override {
        // Optionally implement if contact points are needed
    }

    void reportErrorWarning(const char* warningString) override {
        std::cerr << "Bullet Warning: " << warningString << std::endl;
    }

    void draw3dText(const btVector3& location, const char* textString) override {
        // Optionally implement if 3D text rendering is needed
    }

    void setDebugMode(int debugMode) override {
        this->debugMode = debugMode;
    }

    int getDebugMode() const override {
        return debugMode;
    }

    void render() {
        // glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // glBufferSubData(GL_ARRAY_BUFFER, 0, lines.size() * sizeof(Line), lines.data());

        // glBindVertexArray(vao);
        // glDrawArrays(GL_LINES, 0, lines.size() * 2); // 2 vertices per line
        // glBindVertexArray(0);

        // mesh->draw();

        // lines.clear();
    }

private:
    // struct Line {
    //     glm::vec3 start;
    //     glm::vec3 end;
    //     glm::vec3 color;
    // };
    // std::vector<DebugDrawGeo::Line> lines {};
    int debugMode;
};