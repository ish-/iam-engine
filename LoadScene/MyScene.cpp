#include "MyScene.hpp"
#include "Engine/GUI.hpp"
#include "Engine/Actor.hpp"
#include "Engine/PlayerPhy.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

#include "Engine/Physics/PhysicsComp.hpp"
#include "AEnemy.hpp"
#include "Engine/common/random.hpp"
#include "Engine/common/screenToWorld.hpp"

// MyScene::MyScene () {}

void MyScene::init () {
  Scene::init();

  newActor<PlayerPhy>();

  for (size_t i = 0; i < 10; i++) {
    newActor<AEnemy>((AEnemy::Conf){
      .transform = Transform(rd::vec3in(-30, 30), rd::vec3in(-3.14, 3.14)).getTransformMatrix(),
      .physics = (PhysicsComp::Params){
        .mass = 1.,
        .damping = glm::vec2(.3, .3),
        .group = PhysicsComp::ENEMY,
      }
    });
  }

  // loadJson("resources/scenes/scene.json");
  loadJson("resources/scenes/box.json");


}

void MyScene::update (const float& dt) {
  Scene::update(dt);
};

// #include "Engine/Inputs/Inputs.hpp"
// #include "Engine/Graphics/Window.hpp"
// #include "Engine/Physics/Ray.hpp"
// void MyScene::castMouseRay () {
//   auto inputs = Inputs::get();
//   auto w = Window::get();
//   vec3 worldMouseDir = screenToWorldDir(inputs.mouse.x, inputs.mouse.y, w.width, w.height,
//     camera->getAbsTransformMatrix(), camera->projection);
//   // Ray ray;
//   Ray ray (+Transform(player->getAbsTransformMatrix()).getPosition());
//   if (PhysicsComp* phyComp = ray.castInDir(+worldMouseDir, 100).getHitPhysicsComp())
//     phyComp->getOwner()->getComp<MeshComp>()->conf.tint = vec3(0, 0, 1);
// }

void MyScene::drawGui () {
  Scene::drawGui();

  ImVec2 cursorPos = ImGui::GetIO().MousePos;
  ImDrawList* drawList = ImGui::GetForegroundDrawList();
  drawList->AddLine(ImVec2(cursorPos.x - 5, cursorPos.y), ImVec2(cursorPos.x + 5, cursorPos.y), IM_COL32(255, 0, 0, 255), 2.0f);
  drawList->AddLine(ImVec2(cursorPos.x, cursorPos.y - 5), ImVec2(cursorPos.x, cursorPos.y + 5), IM_COL32(255, 0, 0, 255), 2.0f);
  // IMgui
}