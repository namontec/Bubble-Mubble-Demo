#pragma once

#include "cocos2d.h"

class GameObject;

class PhysicComponent
{
public:
  PhysicComponent();
  virtual ~PhysicComponent();

  virtual void update(GameObject* gameObject, float deltaTime);
  virtual void fixedUpdate(GameObject* gameObject, float deltaTime);

  void          setVelocity(cocos2d::Vec2 velocity);
  cocos2d::Vec2 getVelocity();

  void          setGravity(cocos2d::Vec2 gravity);
  cocos2d::Vec2 getGravity();

  void          setSpeed(float speed);
  float         getSpeed();

  virtual PhysicComponent* clone();

private:
  cocos2d::Vec2 vector_;
  cocos2d::Vec2 velocity_;
  cocos2d::Vec2 gravity_;
  float         speed_;    // initial speed of object
};

