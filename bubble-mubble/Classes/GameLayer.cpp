#include "GameLayer.h"
#include "Globals.h"
#include <memory>
//#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameLayer::createScene()
{
  auto scene = Scene::create();
  auto layer = GameLayer::create();
  scene->addChild(layer);
  return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
  if (!Layer::init()) {
    return false;
  }

  screenSize_ = Director::getInstance()->getWinSize();

  auto spriteCache = SpriteFrameCache::getInstance();
  spriteCache->addSpriteFramesWithFile(Globals::fileNameSpriteSheet);

  auto sprite = Sprite::createWithSpriteFrameName(Globals::fileNameBackground);
  sprite->setAnchorPoint(Vec2(0,0));
  this->addChild(sprite);

  //mouse events
  auto mouseListener = EventListenerMouse::create();
  mouseListener->onMouseMove = CC_CALLBACK_1(GameLayer::onMouseMove, this);
  mouseListener->onMouseDown = CC_CALLBACK_1(GameLayer::onMouseDown, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

  this->scheduleUpdate();
  return true;
}

void GameLayer::update(float deltaTime)
{

}

cocos2d::Vec2 GameLayer::getMousePosition()
{
  return mousePosition_;
}

void GameLayer::onMouseMove(cocos2d::Event * event)
{
  EventMouse* e = (EventMouse*)event;
  mousePosition_ = e->getLocation();
}

void GameLayer::onMouseDown(cocos2d::Event * event)
{

}


