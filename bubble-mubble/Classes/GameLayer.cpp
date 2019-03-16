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


bool GameLayer::init()
{
  if (!Layer::init()) {
    return false;
  }

  //initialize variables
  screenSize_ = Director::getInstance()->getWinSize();
  score_ = 0;
  timer_ = Globals::timer;

  //initialize sprites
  auto spriteCache = SpriteFrameCache::getInstance();
  spriteCache->addSpriteFramesWithFile(Globals::fileNameSpriteSheet);

  //Add background
  auto sprite = Sprite::createWithSpriteFrameName(Globals::fileNameBackground);
  sprite->setAnchorPoint(Vec2(0,0));
  this->addChild(sprite, Globals::BACKGROUND);

  //Add clock
  sprite = Sprite::createWithSpriteFrameName(Globals::fileNameClock);
  sprite->setScale(0.5f);
  sprite->setPosition(Vec2(sprite->getBoundingBox().size.width , screenSize_.height/* - sprite->getBoundingBox().size.height*/));
  this->addChild(sprite, Globals::FOREGROUND);

  //Add cannon stand
  sprite = Sprite::createWithSpriteFrameName(Globals::fileNameStand);
  sprite->setScale(0.2f);
  sprite->setPosition(Vec2(screenSize_.width / 2, 40));
  this->addChild(sprite);


  //Add aim cursor
  aim_ = std::make_unique<GameObject>(Globals::fileNameAim, 0.5f);
  aim_->setPosition(Vec2(screenSize_.width / 2, screenSize_.height / 2));
  aim_->setParent(this, Globals::FOREGROUND);


  //Add cannon ball
  spawner_.addPrototype("ball", Globals::fileNameCannonBall, 0.2f);

  //Target
  spawner_.addPrototype("target", Globals::fileNameTarget, 0.2f);
  sprite = spawner_.spawn("target")->getSprite();
  sprite->setPosition(Vec2(200, 600));
  sprite->setScale(0.2f);
  this->addChild(sprite);

  //Bomb
  sprite = Sprite::createWithSpriteFrameName(Globals::fileNameBomb);
  sprite->setPosition(Vec2(300, 500));
  sprite->setScale(0.2f);
  this->addChild(sprite);





  //Add cannon
  cannon_ = std::make_unique<Canon>(Globals::fileNameCannon, 0.2f, &spawner_, "ball");
  cannon_->setPosition(Vec2(screenSize_.width / 2, 80));
  cannon_->getSprite()->setAnchorPoint(Vec2(0.5f, 1.0f / 3.0f));
  cannon_->setParent(this);


  //Add mouse events listener
  auto mouseListener = EventListenerMouse::create();
  mouseListener->onMouseMove = CC_CALLBACK_1(GameLayer::onMouseMove, this);
  mouseListener->onMouseDown = CC_CALLBACK_1(GameLayer::onMouseDown, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

  this->scheduleUpdate();
  return true;
}


void GameLayer::update(float deltaTime)
{

  //Control cannon rotation
  cannon_->setRotationToVector(getMousePosition());
  aim_->setPosition(getMousePosition());
}


const cocos2d::Vec2 GameLayer::getMousePosition()
{
  return mousePosition_;
}


void GameLayer::onMouseMove(cocos2d::Event * event)
{
  EventMouse* e = (EventMouse*)event;
  mousePosition_.x = e->getCursorX();
  mousePosition_.y = e->getCursorY();
}


void GameLayer::onMouseDown(cocos2d::Event * event)
{
  cannon_->fireCanon(mousePosition_, this);
}


