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
  inputState_.setMousePosition(Vec2(screenSize_.width / 2, screenSize_.height / 2));

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
  clock_->getGraphic()->setPosition(Vec2(clock_->getGraphic()->getNode()->getBoundingBox().size.width, screenSize_.height));
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
  PhysicComponent*  physic = new PhysicComponent();
  graphic->setScale(0.2f);
  auto gameObject = new GameObject(graphic, physic);
  spawner_.addPrototype(gameObject, "ball");
 

  //Add target to spawner
  graphic = new GraphicComponent(Globals::fileNameTarget);
  physic = new PhysicComponent();
  graphic->setScale(0.2f);
  gameObject = new GameObject(graphic, physic);
  spawner_.addPrototype(gameObject, "target");

  //Add bomb to spawner
  graphic = new GraphicComponent(Globals::fileNameBomb);
  graphic->setScale(0.2f);
  gameObject = new GameObject(graphic);
  spawner_.addPrototype(gameObject, "bomb");
  
  //Spawn Targets
  int x, y, velX, velY;
  for (int i = 0; i < Globals::CountTarget; i++) {
    gameObject = spawner_.spawn("target");
    x = Globals::random(50, screenSize_.width-50);
    y = Globals::random(50, screenSize_.height-50);
    velX = Globals::random(-100, 100);
    velY = Globals::random(-100, 100);
    gameObject->getGraphic()->setPosition(Vec2(x, y));
    gameObject->getPhysic()->setVelocity(Vec2(velX, velY));
    gameObject->getGraphic()->setParentNode(this);
    objectsPool_.push_back(std::shared_ptr<GameObject>(gameObject));
  }

  //Add cannon
  InputComponent*   input  = new PlayerInputComponent(&inputState_);
  physic = new PhysicComponent();
  graphic = new GraphicComponent(Globals::fileNameCannon);
  cannon_ = std::make_unique<Canon>(&spawner_, "ball", &objectsPool_, this, graphic, physic, input);
  cannon_->getGraphic()->setScale(0.2f);
  cannon_->getGraphic()->setPosition(Vec2(screenSize_.width / 2, 80));
  cannon_->getGraphic()->setAnchorPoint(Vec2(0.5f, 1.0f / 3.0f));
  cannon_->getGraphic()->setParentNode(this);


  //Add mouse events listener
  auto mouseListener = EventListenerMouse::create();
  mouseListener->onMouseMove = CC_CALLBACK_1(GameLayer::onMouseMove, this);
  mouseListener->onMouseDown = CC_CALLBACK_1(GameLayer::onMouseDown, this);
  mouseListener->onMouseUp = CC_CALLBACK_1(GameLayer::onMouseUp, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

  this->scheduleUpdate();
  return true;
}


void GameLayer::update(float deltaTime)
{
  cannon_->update(deltaTime);

  aim_->getGraphic()->setPosition(getMousePosition());

  for (auto object : objectsPool_) {
    object->update(deltaTime);
  }
}


const cocos2d::Vec2 GameLayer::getMousePosition()
{
  return inputState_.getMousePosition();
}


void GameLayer::onMouseMove(cocos2d::Event * event)
{
  EventMouse* e = (EventMouse*)event;
  cocos2d::Vec2 newMousePosition;
  newMousePosition.x = e->getCursorX();
  newMousePosition.y = e->getCursorY();
  inputState_.setMousePosition(newMousePosition);

}


void GameLayer::onMouseDown(cocos2d::Event * event)
{
  inputState_.setMouseDown(true);
}


void GameLayer::onMouseUp(cocos2d::Event * event)
{
  inputState_.setMouseDown(false);
}


std::list<std::shared_ptr<GameObject>>* GameLayer::getObjectPool()
{
  return &objectsPool_;
}


