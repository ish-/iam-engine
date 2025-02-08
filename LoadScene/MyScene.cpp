#include "MyScene.hpp"
#include "GUI.hpp"
#include "Actor.hpp"
#include "common/json.hpp"
#include "PlayerPhy.hpp"

// MyScene::MyScene () {}

void MyScene::init () {
  Scene::init();

  newActor<PlayerPhy>();

  loadJson("resources/scenes/scene.json");
}

void MyScene::update(float dt) {
  // getActorByName("my-cube")->rotate(vec3(dt));

  Scene::update(dt);
};

void MyScene::drawGui () {
  Scene::drawGui();

  // IMgui
}