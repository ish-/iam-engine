#include "ParticlesSample.hpp"

#include "Window.hpp"
#include "Inputs/Inputs.hpp"
#include "Graphics/Renderer.hpp"
#include "Engine/Camera.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

#include <cstdlib>
#include <ctime>

using namespace glm;

float boxVerts[] = {
    // x, y, z
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f
};
unsigned int boxInds[] = {
    0, 1, 2,
    2, 3, 0,
    4, 5, 6,
    6, 7, 4,
    0, 3, 7,
    7, 4, 0,
    1, 5, 6,
    6, 2, 1,
    0, 1, 5,
    5, 4, 0,
    3, 2, 6,
    6, 7, 3
};

void ParticlesSample::load() {
    computeShader =  make_shared<Shader>(Shader::Opts{
        .compPath = "shaders/Particles.comp.glsl"});
    renderShader = make_shared<Shader>(Shader::Opts{
        .vertPath = "shaders/Particles.vert.glsl",
        .fragPath = "shaders/Particles.frag.glsl"
    });

    renderer = Renderer::getPtr();

    static const vec3 pointGeo[] = { vec3(0) };

    glGenBuffers(1, &pointsBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, pointsBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, POINTS_SIZE * sizeof(ParticlePoint), NULL, GL_DYNAMIC_COPY);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, pointsBuffer);

    InitBuffer();


    /// BOX
    glGenBuffers(1, &pointGeoBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, pointGeoBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boxVerts), boxVerts, GL_STATIC_DRAW);

    unsigned int boxEBO;
    glGenBuffers(1, &boxEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxInds), boxInds, GL_STATIC_DRAW);

    glGenVertexArrays(1, &pointRenderVao);

    glBindVertexArray(pointRenderVao);
    glBindBuffer(GL_ARRAY_BUFFER, pointGeoBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boxEBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)(1 * sizeof(vec3)));

    glBindBuffer(GL_ARRAY_BUFFER, pointsBuffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ParticlePoint), NULL);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(ParticlePoint), (void *)sizeof(vec4));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    // per-instance
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
}

void ParticlesSample::update(float dt) {
    totalTime += dt;

    auto inputs = Inputs::get();
    if (inputs.btnRel[SDLK_R] > 0.)
        InitBuffer();

    renderer->setShader(computeShader);
    computeShader->setUniform("Time", totalTime / 10.f);
    computeShader->setUniform("CamPos", camera->getAbsPosition());

    glDispatchCompute(NUM_WORKGROUPS, 1, 1);
}

void ParticlesSample::draw()
{
    auto w = Window::get();
    renderer->setShader(renderShader);

    renderShader->setUniform("mvp", camera->projection * glm::inverse(camera->getAbsTransformMatrix()));
    renderShader->setUniform("CamPos", camera->getAbsPosition());
    renderShader->setUniform("InstanceScale", .03f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindVertexArray(pointRenderVao);
    // glDrawArraysInstanced(GL_POINTS, 0, 1, POINTS_SIZE);    
    glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, POINTS_SIZE);
}

void ParticlesSample::InitBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, pointsBuffer);
    ParticlePoint * ptr = reinterpret_cast<ParticlePoint *>(
        glMapBufferRange(GL_ARRAY_BUFFER, 0, POINTS_SIZE * sizeof(ParticlePoint),
                         GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT)
    );

    for (int i = 0; i < POINTS_SIZE; i++)
    {
        ptr[i].pos = rd::vec3in(-15,15);
        ptr[i].vel = rd::vec3in(-.5,.5);
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
}
