#include "Canon.h"



Canon::Canon(const std::string& fileName, float scale, Spawner* spawner, const std::string& ballName)
  : GameObject(fileName, scale), spawner_(spawner), ballName_(ballName)
{
}


Canon::~Canon()
{
}


void Canon::setRotationToVector(const cocos2d::Vec2 coordinates)
{
  cocos2d::Vec2 canonPosition = getPosition();
  cocos2d::Vec2 vector = (coordinates - canonPosition);

  float angle = vector.getNormalized().getAngle();
  angle = -(MATH_RAD_TO_DEG(angle) - 90);

  if (angle > 180) {
    angle = -90;
  }
  if (angle > 90 && angle < 180) {
    angle = 90;
  }

  getSprite()->setRotation(angle);
}


void Canon::setRotation(float angle)
{
  getSprite()->setRotation(angle);
}


float Canon::getRotation()
{
  return getSprite()->getRotation();
}


void Canon::fireCanon(cocos2d::Vec2 direction, cocos2d::Layer* layer)
{
  auto ball = std::shared_ptr<GameObject>(spawner_->spawn(ballName_));
  auto sprite = ball->getSprite();
  layer->addChild(sprite);
}



