
#include "GameOverScene.h"
#include "Globals.h"

USING_NS_CC;

Scene* GameOverScene::createScene(int tLost, int tTotal)
{
  auto scene = Scene::create();
  auto layer = GameOverScene::create();
  layer->targetsDestroyesd = tTotal - tLost;
  layer->targetsTotal = tTotal;
  scene->addChild(layer);
  return scene;
}

bool GameOverScene::init()
{
  if (!Layer::init()) {
    return false;
 }

  auto size = Director::getInstance()->getWinSize();

  //Add labels
  std::string title;
  bool win = targetsDestroyesd <= 0;
  if (win) {
    title = "Congratulations! You WIN!";
  }
  else {
    title = "Game Over! You LOSE!";
  }

  std::string totals = "Destroyed " + std::to_string(targetsDestroyesd) + "from " + std::to_string(targetsTotal);

  labelTitle_ = Label::createWithTTF(title, "fonts/Marker Felt.ttf", 180);
  labelTitle_->setHorizontalAlignment(TextHAlignment::CENTER);
  labelTitle_->setPosition(screenSize_ /2);
  this->addChild(labelTitle_, Globals::FOREGROUND);

  labelDestroyed_ = Label::createWithTTF(totals, "font/Marker felt.ttf", 80);
  labelDestroyed_->setHorizontalAlignment(TextHAlignment::CENTER);
  labelDestroyed_->setPosition(Vec2(screenSize_.width / 2 + labelDestroyed_->getBoundingBox().size.width / 2, screenSize_.height - timerLabel_->getBoundingBox().size.height));
  this->addChild(timerLabel_, Globals::FOREGROUND);
  return true;
}

