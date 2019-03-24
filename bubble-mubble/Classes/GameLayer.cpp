#include "GameLayer.h"
#include "Globals.h"
#include <memory>
#include <iostream>
#include <math.h>
#include <chrono>
#include "Settings.h"
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
  //Load external variables
  Settings settings(Globals::fileNameSettings);
  std::string tempString;
  settings.init();
  tempString = settings.getValue("CountTarget");
  if (!tempString.empty()) {
    Globals::CountTarget = std::stoi(tempString);
  }
  tempString = settings.getValue("Speed");
  if (!tempString.empty()) {
    Globals::BallSpeed = std::stoi(tempString);
  }
  tempString = settings.getValue("Time");
  if (!tempString.empty()) {
    Globals::timer = std::stoi(tempString);
  }
  tempString = settings.getValue("NumberOfCannons");
  if (!tempString.empty()) {
    Globals::NumberOfCannons = std::stoi(tempString);
  }
  ////

  //initialize variables
  screenSize_ = Director::getInstance()->getWinSize();
  isGameOver_ = false;
  timer_ = Globals::timer;
  score_ = 0;
  inputState_.setMousePosition(Vec2(screenSize_.width / 2, screenSize_.height / 2));


  //Initialize sprites (spawner_)
  initSprites();
 
  //Spawn Background
  background_ = std::unique_ptr<GameObject>(spawner_.spawn("background"));
  background_->getGraphic()->setParentNode(this, Globals::BACKGROUND);

  //Spawn Clock
  clock_ = std::unique_ptr<GameObject>(spawner_.spawn("clock"));
  clock_->getGraphic()->setParentNode(this, Globals::FOREGROUND);

  //Add clock timer Label
  timerLabel_ = Label::createWithTTF(std::to_string(timer_), "fonts/Marker Felt.ttf", 60);
  timerLabel_->setHorizontalAlignment(TextHAlignment::LEFT);
  timerLabel_->setPosition(Vec2(screenSize_.width / 2 + timerLabel_->getBoundingBox().size.width / 2, screenSize_.height - timerLabel_->getBoundingBox().size.height));
  this->addChild(timerLabel_, Globals::FOREGROUND);

  //Spawn Cursor Aim
  aim_ = std::unique_ptr<GameObject>(spawner_.spawn("aim"));
  aim_->getGraphic()->setParentNode(this, Globals::FOREGROUND);


  //Add mouse events listener
  auto mouseListener = EventListenerMouse::create();
  mouseListener->onMouseMove = CC_CALLBACK_1(GameLayer::onMouseMove, this);
  mouseListener->onMouseDown = CC_CALLBACK_1(GameLayer::onMouseDown, this);
  mouseListener->onMouseUp = CC_CALLBACK_1(GameLayer::onMouseUp, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);


  this->scheduleUpdate();
  startTheGame();

  return true;
}


void GameLayer::initSprites()
{
  //initialize sprites
  auto spriteCache = SpriteFrameCache::getInstance();
  spriteCache->addSpriteFramesWithFile(Globals::fileNameSpriteSheet);

  GraphicComponent* graphic;
  PhysicComponent*  physic;
  InputComponent*   input;
  AbstractUpdate*   customUpdate;
  GameObject*       gameObject;

  //Add background
  graphic = new GraphicComponent(Globals::fileNameBackground);
  graphic->setAnchorPoint(Vec2::ZERO);
  gameObject = new GameObject(graphic);
  spawner_.addPrototype(gameObject, "background");

  //Add clock
  graphic = new GraphicComponent(Globals::fileNameClock);
  gameObject = new GameObject(graphic);
  gameObject->getGraphic()->setAnchorPoint(Vec2(0.5f, 0.5f));
  gameObject->getGraphic()->setScale(0.5f);
  auto clockSize = gameObject->getGraphic()->getNode()->getBoundingBox().size;
  gameObject->getGraphic()->setPosition(Vec2(screenSize_.width / 2 - clockSize.width / 2, screenSize_.height - clockSize.height / 1.8f));
  spawner_.addPrototype(gameObject, "clock");

  //Add cannon stand
  graphic = new GraphicComponent(Globals::fileNameStand);
  gameObject = new GameObject(graphic);
  gameObject->getGraphic()->setScale(0.2f);
  gameObject->getGraphic()->setPosition(Vec2(screenSize_.width / 2, 40));
  spawner_.addPrototype(gameObject, "stand");

  //Add aim cursor
  graphic = new GraphicComponent(Globals::fileNameAim);
  gameObject = new GameObject(graphic);
  gameObject->getGraphic()->setScale(0.5f);
  gameObject->getGraphic()->setPosition(Vec2(screenSize_.width / 2, screenSize_.height / 2));
  spawner_.addPrototype(gameObject, "aim");

  //Add cannon Ball to spawner
  graphic = new GraphicComponent(Globals::fileNameCannonBall);
  physic = new PhysicComponent();
  input = nullptr;
  customUpdate = new BallUpdate();
  graphic->setScale(0.2f);
  physic->setSpeed(Globals::BallSpeed);
  physic->setGravity(cocos2d::Vec2(0, Globals::Gravity));
  gameObject = new GameObject(graphic, physic, input, customUpdate);
  gameObject->setTag(Globals::CANNONBALL);
  spawner_.addPrototype(gameObject, "ball");

  //Add target1 to spawner
  graphic = new GraphicComponent(Globals::fileNameTarget);
  physic = new PhysicComponent();
  input = nullptr;
  customUpdate = new TargetUpdate();
  graphic->setScale(0.2f);
  physic->setSpeed(100.0f);
  gameObject = new GameObject(graphic, physic, input, customUpdate);
  gameObject->setTag(Globals::TARGET);
  spawner_.addPrototype(gameObject, "target1");

  //Add target2 from prototype to spawner
  gameObject = spawner_.spawn("target1");
  gameObject->getGraphic()->setScale(0.3f);
  gameObject->getPhysic()->setSpeed(50.0f);
  //gameObject->getGraphic()->setColor(Color3B::GREEN);
  spawner_.addPrototype(gameObject, "target2");

  //Add target2 from prototype to spawner
  gameObject = spawner_.spawn("target1");
  gameObject->getGraphic()->setScale(0.1f);
  gameObject->getPhysic()->setSpeed(200.0f);
  //gameObject->getGraphic()->setColor(Color3B::RED);
  spawner_.addPrototype(gameObject, "target3");

  //Add bomb to spawner
  graphic = new GraphicComponent(Globals::fileNameBomb);
  graphic->setScale(0.2f);
  gameObject = new GameObject(graphic);
  spawner_.addPrototype(gameObject, "bomb");

  //Add cannon
  input = new PlayerInputComponent(&inputState_);
  physic = new PhysicComponent();
  graphic = new GraphicComponent(Globals::fileNameCannon);
  gameObject = new Canon(&spawner_, "ball", &objectsPool_, this, graphic, physic, input);
  gameObject->getGraphic()->setScale(0.2f);
  gameObject->getGraphic()->setPosition(Vec2(screenSize_.width / 2, 80));
  gameObject->getGraphic()->setAnchorPoint(Vec2(0.5f, 1.0f / 3.0f));
  gameObject->setTag(Globals::CANNON);
  //add spawn position (create empty Node)
  graphic = new GraphicComponent();
  graphic->setAnchorPoint(Vec2(0.5f, 0.5f));
  graphic->setPosition(Vec2(325, 730));
  auto gameObjectChild = new GameObject(graphic);
  gameObject->setChild(gameObjectChild);
  /////
  spawner_.addPrototype(gameObject, "cannon");
}



void GameLayer::startTheGame()
{
  Director::getInstance()->getOpenGLView()->setCursorVisible(false);

  objectsPool_.clear();
  timer_ = Globals::timer;
  targetsLast_ = Globals::CountTarget;

  //Spawn Targets
  float x, y, velX, velY, angle;
  int   selectedTarget;
  Size  nodeSize;
  GameObject* gameObject;
  std::map<int, std::string> targets{ {1, "target1"}, {2, "target2"}, {3, "target3"} };

  for (int i = 0; i < Globals::CountTarget; i++) {
    selectedTarget = Globals::random(1, targets.size());
    gameObject = spawner_.spawn(targets[selectedTarget]);
    nodeSize = gameObject->getGraphic()->getNode()->getBoundingBox().size;
    float distFromBound = 30.0f;
    x = static_cast<float>( Globals::random(nodeSize.width / 2.0f + distFromBound, screenSize_.width - distFromBound - nodeSize.width / 2.0f) );
    y = static_cast<float>( Globals::random(nodeSize.width / 2.0f + (distFromBound * 2.0f), screenSize_.height - nodeSize.height / 2.0f) );

    angle = Globals::random(0, 359);
    angle = angle * std::_Pi / 180;
    velX = std::cos(angle) * gameObject->getPhysic()->getSpeed();
    velY = std::sin(angle) * gameObject->getPhysic()->getSpeed();
    gameObject->getGraphic()->setPosition(Vec2(x, y));
    gameObject->getPhysic()->setVelocity(Vec2(velX, velY));
    gameObject->getGraphic()->setParentNode(this);
    objectsPool_.push_back(std::shared_ptr<GameObject>(gameObject));
  }


  //Spawn Cannons
  for (int i = 0; i < Globals::NumberOfCannons; i++) {
    int x = screenSize_.width / (Globals::NumberOfCannons + 1) * (i + 1);

    auto object = std::shared_ptr<GameObject>(spawner_.spawn("stand"));
    object->getGraphic()->setPosition(Vec2(x, 40));
    object->getGraphic()->setParentNode(this, Globals::BACKGROUND);
    objectsPool_.push_back(object);

    object = std::shared_ptr<Canon>(static_cast<Canon*>(spawner_.spawn("cannon")));
    object->getGraphic()->setPosition(Vec2(x, 80));
    object->getGraphic()->setParentNode(this);
    objectsPool_.push_back(object);
  }

  isGameOver_ = false;
  startTimer(timerLabel_);
}



void GameLayer::startTimer(cocos2d::Label * label)
{
  this->schedule([=](float deltaTime) {
    bool allTargetsDestroyed = (targetsLast_ <= 0);

    if ((timer_ < 0) || allTargetsDestroyed) {
      this->unschedule("timerTick");
      isGameOver_ = true;
      return;
    }
    timerLabel_->setString(std::to_string(timer_));
    timer_--;

  }, 1.0f, "timerTick");
}



void GameLayer::update(float deltaTime)
{

  aim_->getGraphic()->setPosition(getMousePosition());
 
  if (isGameOver_) {
    GameOverScene::targetsDestroyed = Globals::CountTarget - targetsLast_;
    GameOverScene::targetsTotal = Globals::CountTarget;

    auto scene = GameOverScene::createScene();
    Director::getInstance()->replaceScene(scene);
  }

  //Update or delete objects from pool
  for (auto p = objectsPool_.begin(); p != objectsPool_.end(); p++) {

    if ((*p)->isReadyToDie) {
      if ((*p)->getTag() == Globals::TARGET) {
        targetsLast_--;
      }
      //// ADD EXPLOSION PARTICLE
      auto particleExplosion = cocos2d::ParticleSystemQuad::create(Globals::fileNameParticleExplosion);
      particleExplosion->setScale(2.0f);
      auto objectPosition = (*p)->getGraphic()->getPosition();
      particleExplosion->setPosition(objectPosition);
      this->addChild(particleExplosion, Globals::FOREGROUND);
      ////
      p = objectsPool_.erase(p); // remove object from pool

      bool pIsEndIterator = (p == objectsPool_.end());
      if (pIsEndIterator) break;
    }
    else {
      (*p)->update(deltaTime);
    }
  }

  //Perfom Fixed Update for physic events
  fixedTimeCounter += deltaTime;
  while (fixedTimeCounter > fixedTimePeriod) {
    fixedUpdate(fixedTimePeriod);
    fixedTimeCounter -= fixedTimePeriod;
  }
}


void GameLayer::fixedUpdate(float deltaTime)
{
  for (auto object : objectsPool_) {
    object->fixedUpdate(deltaTime);
  }

  for (auto p = objectsPool_.begin(); p != objectsPool_.end(); p++) {

    //Check Bounds collisons
    checkBounds(*p);

    //Compare (*p) object collisions with others objects
    auto objectTag = (*p)->getTag();

    for (auto p2 = p; p2 != objectsPool_.end(); p2++) {
      if ((*p2) == (*p)) continue;
;
      auto otherObjectTag = (*p2)->getTag();

      float isIntersected = (*p)->intersectsObject(*p2);
      if (isIntersected) {

        bool hitCanonballAndTarget = (objectTag == Globals::CANNONBALL) && (otherObjectTag == Globals::TARGET);
        bool hitTargetAndCanonball = (objectTag == Globals::TARGET) && (otherObjectTag == Globals::CANNONBALL);
        bool hitTargetAndTarget = (objectTag == Globals::TARGET) && (otherObjectTag == Globals::TARGET);
        bool hitTargetAndCannon = (objectTag == Globals::TARGET) && (otherObjectTag == Globals::CANNON);
        bool hitCannonAndTarget = (objectTag == Globals::CANNON) && (otherObjectTag == Globals::TARGET);

        if (hitCanonballAndTarget) {
          (*p)->isReadyToDie = true;
          (*p2)->isReadyToDie = true;
        }
        else if (hitTargetAndCanonball) {
          (*p)->isReadyToDie = true;
          (*p2)->isReadyToDie = true;
        }
        else if (hitTargetAndTarget || hitTargetAndCannon || hitCannonAndTarget) {

          auto vel1 = (*p)->getPhysic()->getVelocity();
          auto vel2 = (*p2)->getPhysic()->getVelocity();
          auto pos1 = (*p)->getGraphic()->getPosition();
          auto pos2 = (*p2)->getGraphic()->getPosition();

          if (pos1.x < pos2.x) {
            vel1.x = -std::abs(vel1.x);
            vel2.x = std::abs(vel2.x);
          }
          if (pos1.x > pos2.x) {
            vel1.x = std::abs(vel1.x);
            vel2.x = -std::abs(vel2.x);
          }
          if (pos1.y < pos2.y) {
            vel1.y = -std::abs(vel1.y);
            vel2.y = std::abs(vel2.y);
          }
          if (pos1.y > pos2.y) {
            vel1.y = std::abs(vel1.y);
            vel2.y = -std::abs(vel2.y);
          }

          (*p)->getPhysic()->setVelocity(Vec2(vel1.x, vel1.y));
          (*p2)->getPhysic()->setVelocity(Vec2(vel2.x, vel2.y));
        }
      }
    }
  }
}


//Check bounds of the screen
void GameLayer::checkBounds(std::shared_ptr<GameObject> gameObject)
{
  int  objectTag;
  Vec2 objectPos;
  Size objectSize;

  objectTag = gameObject->getTag();

  objectPos = gameObject->getGraphic()->getPosition();
  objectSize = gameObject->getGraphic()->getNode()->getBoundingBox().size;
  if (objectTag == Globals::CANNONBALL) {
    float distanceToLive = 500.0f;
    bool behindLeft = (objectPos.x + objectSize.width / 2 + distanceToLive) < 0;
    bool behindRight = (objectPos.x - objectSize.width / 2 - distanceToLive) > screenSize_.width;
    bool belowBottom = (objectPos.y + objectSize.height / 2 + distanceToLive) < 0;
    if (behindLeft || behindRight || belowBottom) {
      gameObject->isReadyToDie = true;
    }
  }
  else if (objectTag == Globals::TARGET) {

    bool touchLeft = (objectPos.x - (objectSize.width / 2)) <= 0;
    bool touchRight = (objectPos.x + (objectSize.width / 2)) >= screenSize_.width;
    bool touchBottom = (objectPos.y - (objectSize.height / 2)) <= 60;
    bool touchTop = (objectPos.y + (objectSize.height / 2)) >= screenSize_.height;
    auto velocity = gameObject->getPhysic()->getVelocity();
    if (touchLeft) {
      gameObject->getPhysic()->setVelocity( Vec2(std::abs(velocity.x), velocity.y) );
    }
    if (touchRight) {
      gameObject->getPhysic()->setVelocity( Vec2(- std::abs(velocity.x), velocity.y) );
    }

    if (touchBottom) {
      gameObject->getPhysic()->setVelocity( Vec2(velocity.x, std::abs(velocity.y)) );
    }
    if (touchTop) {
      gameObject->getPhysic()->setVelocity( Vec2(velocity.x, - std::abs(velocity.y)) );
    }
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


