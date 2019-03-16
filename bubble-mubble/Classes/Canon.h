#pragma once

#include "GameObject.h"
#include "Spawner.h"

class Canon :
  public GameObject
{
public:
  Canon(const std::string& fileName, float scale, Spawner* spawner, const std::string& ballName);
  virtual ~Canon();

  void  setRotationToVector(const cocos2d::Vec2 toVector);
  void  setRotation(float angle);
  float getRotation();

  void fireCanon(cocos2d::Vec2 direction, cocos2d::Layer* layer);

private:
  Spawner* spawner_;
  std::string ballName_;
};

