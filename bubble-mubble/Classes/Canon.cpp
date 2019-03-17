#include "Canon.h"



Canon::Canon(Spawner* spawner, const std::string & ballName, GraphicComponent * graphic, PhysicComponent * physic, InputComponent * input)
  :GameObject(graphic, physic, input), spawner_(spawner), ballName_(ballName)
{
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


void Canon::fireCanon(cocos2d::Vec2 targetPosition, cocos2d::Layer* layer)
{
  auto ball = std::shared_ptr<GameObject>(spawner_->spawn(ballName_));
  ball->getGraphic()->setPosition(targetPosition);
  ball->getGraphic()->setParentNode(layer);
}



