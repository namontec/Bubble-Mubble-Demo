#include "Canon.h"
#include <math.h>



Canon::Canon(Spawner* spawner, const std::string & ballName, std::list<std::shared_ptr<GameObject>> *objectsPool, cocos2d::Node* parentNode,
  GraphicComponent * graphic,   PhysicComponent * physic, InputComponent * input)
  :GameObject(graphic, physic, input), spawner_(spawner), ballName_(ballName), parentNode_(parentNode)
{
  objectsPool_ = objectsPool;
}


Canon::~Canon()
{
}


void Canon::setRotationToVector(const cocos2d::Vec2 coordinates)
{
  cocos2d::Vec2 canonPosition = getGraphic()->getPosition();
  cocos2d::Vec2 vector = (coordinates - canonPosition);

  float angle = vector.getNormalized().getAngle();
  angle = -(MATH_RAD_TO_DEG(angle) - 90);

  if (angle > 180) {
    angle = -90;
  }
  if (angle > 90 && angle < 180) {
    angle = 90;
  }

  getGraphic()->setRotation(angle);
}


void Canon::setRotation(float angle)
{
  getGraphic()->setRotation(angle);
}


float Canon::getRotation()
{
  return getGraphic()->getRotation();
}


void Canon::fireCanon(cocos2d::Vec2 targetPosition)
{
  cocos2d::Vec2 direction = (targetPosition - getGraphic()->getPosition()).getNormalized();

  auto ball = std::shared_ptr<GameObject>(spawner_->spawn(ballName_));

  
  auto ballSpawnPosition = getGraphic()->getNode()->convertToWorldSpace( getChild()->getGraphic()->getPosition() );
  ball->getGraphic()->setPosition( ballSpawnPosition );

  ball->getPhysic()->setVelocity( direction * ball->getPhysic()->getSpeed() );
  ball->getGraphic()->setParentNode(parentNode_);

  //// ADD PARTICLE
  auto particleSmokeTrail = cocos2d::ParticleSystemQuad::create(Globals::fileNameParticleSmokeTrail);
  particleSmokeTrail->setScale(9.0f);
  particleSmokeTrail->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
  auto ballSize = ball->getGraphic()->getNode()->getContentSize();
  particleSmokeTrail->setPosition(cocos2d::Vec2(ballSize.width / 2, ballSize.height / 2));
  ball->getGraphic()->getNode()->addChild(particleSmokeTrail, Globals::BACKGROUND);
  ////

  objectsPool_->push_back(ball);
}


GameObject * Canon::clone()
{
  GraphicComponent* graphic = nullptr;
  PhysicComponent*  physic = nullptr;
  InputComponent*   input = nullptr;
  AbstractUpdate*   customUpdate = nullptr;

  if (input_) {
    input = input_->clone();
  }

  if (physic_) {
    physic = physic_->clone();
  }

  if (graphic_) {
    graphic = graphic_->clone();
  }

  if (customUpdate_) {
    customUpdate = customUpdate_->clone();
  }

  //create clone of GameObject
  auto object = new Canon(spawner_, ballName_, objectsPool_, parentNode_, graphic, physic, input);

  //clone some variables
  object->setTag(tag_);

  //clone child object
  if (getChild()) {
    auto childObject = getChild()->clone();
    object->setChild(childObject);
  }

  return object;
}

void Canon::update(float deltatime)
{
  auto mousePosition = getInput()->getInputState()->getMousePosition();
  setRotationToVector(mousePosition);

  bool waitForCoolDown = coolTimer > 0;
  if (waitForCoolDown) {
    coolTimer -= deltatime;
  }

  bool mouseIsDown = getInput()->getInputState()->getMouseDown();
  if (mouseIsDown) {
    bool readyToFire = coolTimer <= 0;
    if (readyToFire) {
      coolTimer += coolTimeInterval;
      fireCanon(mousePosition);
    }

  }

}



