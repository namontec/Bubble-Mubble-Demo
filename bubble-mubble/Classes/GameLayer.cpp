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
  mousePosition_ = Vec2(screenSize_.width / 2, screenSize_.height  / 2);

  //initialize sprites
  auto spriteCache = SpriteFrameCache::getInstance();
  spriteCache->addSpriteFramesWithFile(Globals::fileNameSpriteSheet);

  //Add background
  GraphicComponent* graphic = new GraphicComponent(Globals::fileNameBackground);
  background_ = std::make_unique<GameObject>(graphic);
  background_->getGraphic()->setAnchorPoint(Vec2::ZERO);
  background_->getGraphic()->setParentNode(this, Globals::BACKGROUND);
 
  

  //Add clock
  graphic = new GraphicComponent(Globals::fileNameClock);
  clock_ = std::make_unique<GameObject>(graphic);
  clock_->getGraphic()->setScale(0.5f);
  clock_->getGraphic()->setPosition(Vec2(clock_->getGraphic()->getSprite()->getBoundingBox().size.width, screenSize_.height));
  clock_->getGraphic()->setParentNode(this, Globals::FOREGROUND);
  

  //Add cannon stand
  graphic = new GraphicComponent(Globals::fileNameStand);
  cannonStand_ = std::make_unique<GameObject>(graphic);
  cannonStand_->getGraphic()->setScale(0.2f);
  cannonStand_->getGraphic()->setPosition(Vec2(screenSize_.width / 2, 40));
  cannonStand_->getGraphic()->setParentNode(this);
  

  //Add aim cursor
  graphic = new GraphicComponent(Globals::fileNameAim);
  aim_ = std::make_unique<GameObject>(graphic);
  aim_->getGraphic()->setScale(0.5f);
  aim_->getGraphic()->setPosition(Vec2(screenSize_.width / 2, screenSize_.height / 2));
  aim_->getGraphic()->setParentNode(this, Globals::FOREGROUND);
  
  
  //Add cannon ball to spawner
  graphic = new GraphicComponent(Globals::fileNameCannonBall);
  graphic->setScale(0.2f);
  auto gameObject = new GameObject(graphic);
  spawner_.addPrototype(gameObject, "ball");
 

  //Add target to spawner
  graphic = new GraphicComponent(Globals::fileNameTarget);
  graphic->setScale(0.2f);
  auto gameObject = new GameObject(graphic);
  spawner_.addPrototype(gameObject, "target");

  //Add bomb to spawner
  graphic = new GraphicComponent(Globals::fileNameBomb);
  graphic->setScale(0.2f);
  auto gameObject = new GameObject(graphic);
  spawner_.addPrototype(gameObject, "bomb");
  


  //Add cannon
  InputComponent*   input   = new PlayerInputComponent();
  PhysicComponent*  physic  = new PhysicComponent();
  graphic = new GraphicComponent(Globals::fileNameCannon);
  cannon_ = std::make_unique<Canon>(&spawner_, "ball", graphic, physic, input);
  cannon_->getGraphic()->setScale(0.2f);
  cannon_->getGraphic()->setPosition(Vec2(screenSize_.width / 2, 80));
  cannon_->getGraphic()->setAnchorPoint(Vec2(0.5f, 1.0f / 3.0f));
  cannon_->getGraphic()->setParentNode(this);


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
  aim_->getGraphic()->setPosition(getMousePosition());
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


