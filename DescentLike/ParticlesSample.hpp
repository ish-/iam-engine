#pragma once

#include "Engine/Graphics/Shader.hpp"
#include "Engine/Camera.hpp"
// #include "../engine/Scene.h"
// #include "../engine/Assets.h"
// #include "../engine/MeshObject.h"

constexpr int WORKGROUP_SIZE = 64;
constexpr int NUM_WORKGROUPS = 64;
constexpr int POINTS_SIZE = (NUM_WORKGROUPS * WORKGROUP_SIZE);

struct ParticlePoint
{
    glm::vec3 pos;
    unsigned int : 32;
    glm::vec3 vel;
    unsigned int : 32;
};

class ParticlesSample {
public:
    ParticlesSample(sp<Camera>& camera) : camera(camera) {}

    void load();
    void update(float dt);
    void draw();

    void BindACounter();
    void ResetACounter();
    void InitBuffer();
    GLuint ReadACounter();

private:
    sp<Camera>& camera;

    float totalTime = 1.0f;
    unsigned int linesToDraw;

    // class Renderer* renderer;
    shared_ptr<class Renderer> renderer;
    // class Renderer renderer;

    shared_ptr<Shader> computeShader;
    shared_ptr<Shader> renderShader;

    GLuint pointsBuffer;
    GLuint linesBuffer;
    GLuint pointGeoBuffer;
    GLuint linesRenderVao;
    GLuint pointRenderVao;
    GLuint lineGeoBuffer;
    GLuint frameIndex;
    GLuint aCounterBuffer;
    GLuint aCounter = 0;
    float distToDrawLine = 2500.;

    float radius = 100.;
    float fov = 45.;
};


