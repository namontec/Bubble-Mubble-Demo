#pragma once

#include "GameObject.h"
#include "Spawner.h"

class Canon :
  public GameObject
{
public:
  Canon(Spawner* spawner, const std::string& ballName, GraphicComponent* graphic = nullptr, PhysicComponent* physic = nullptr, InputComponent* input = nullptr);
  virtual ~Canon();

  void  setRotationToVector(const cocos2d::Vec2 toVector);
  void  setRotation(float angle);
  float getRotation();

  void fireCanon(cocos2d::Vec2 direction, cocos2d::Layer* layer);

private:
  Spawner* spawner_;
  std::string ballName_;
};

