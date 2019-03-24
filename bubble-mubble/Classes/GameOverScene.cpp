
#include "GameOverScene.h"
#include "Globals.h"
#include "GameLayer.h"

USING_NS_CC;

int GameOverScene::targetsDestroyed = 0;
int GameOverScene::targetsTotal = 0;


Scene* GameOverScene::createScene()
{
  auto scene = Scene::create();
  auto layer = GameOverScene::create();


  scene->addChild(layer);
  return scene;
}

bool GameOverScene::init()
{
  if (!Layer::init()) {
    return false;
 }

  auto size = Director::getInstance()->getWinSize();
  Director::getInstance()->getOpenGLView()->setCursorVisible(true);

  //Add labels
  std::string title;
  bool win = (targetsDestroyed == targetsTotal);
  if (win) {
    title = "Congratulations!";
  }
  else {
    title = "Game Over";
  }

  std::string totals = "Destroyed " + std::to_string(targetsDestroyed) + " targets of " + std::to_string(targetsTotal);

  auto labelTitle = Label::createWithTTF(title, "fonts/Marker Felt.ttf", 100);

  labelTitle->setPosition(Vec2(size.width / 2, (size.height / 5) * 4));
  this->addChild(labelTitle);

  auto labelDestroyed = Label::createWithTTF(totals, "fonts/Marker Felt.ttf", 50);

  labelDestroyed->setPosition(Vec2(size.width / 2, (size.height / 5) *3));
  this->addChild(labelDestroyed);



  auto itemReplay = MenuItemFont::create("Replay", [](Ref* sender) {
    auto scene = GameLayer::createScene();
    Director::getInstance()->replaceScene(scene);
  });

  auto menu = Menu::create(itemReplay, nullptr);
  //menu->alignItemsVertically();
  menu->setPosition(Vec2(size.width / 2, (size.height / 5) * 1.5f));
  this->addChild(menu);

  return true;
}



