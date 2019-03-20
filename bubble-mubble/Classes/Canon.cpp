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
  ball->getGraphic()->setPosition( getGraphic()->getPosition() );

  ball->getPhysic()->setVelocity( direction * ball->getPhysic()->getSpeed() );
  ball->getGraphic()->setParentNode(parentNode_);

  objectsPool_->push_back(ball);
}


void Canon::update(float deltatime)
{
  auto mousePosition = getInput()->getInputState()->getMousePosition();
  setRotationToVector(mousePosition);


  bool mouseIsDown = getInput()->getInputState()->getMouseDown();
  if (mouseIsDown) {
    fireCanon (mousePosition);
  }

}



