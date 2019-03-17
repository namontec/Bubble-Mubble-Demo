#include "PhysicComponent.h"
#include "GameObject.h"


PhysicComponent::PhysicComponent()
{
}


PhysicComponent::~PhysicComponent()
{
}


void PhysicComponent::update(GameObject* gameObject, float deltaTime)
{
  //add velociy to current position every update
  auto graphic = gameObject->getGraphic();
  if (graphic) {
    auto position = graphic->getPosition();
    position += velocity_ * deltaTime;
    graphic->setPosition(position);
  }
}


void PhysicComponent::fixedUpdate(GameObject * gameObject, float deltaTime)
{
  //add gravity to current position every fixedUpdate
  auto graphic = gameObject->getGraphic();
  if (graphic) {
    auto position = graphic->getPosition();
    position += gravity_;
    graphic->setPosition(position);
  }
}


void PhysicComponent::setVelocity(cocos2d::Vec2 velocity)
{
  velocity_ = velocity;
}


cocos2d::Vec2 PhysicComponent::getVelocity()
{
  return velocity_;
}


void PhysicComponent::setGravity(cocos2d::Vec2 gravity)
{
  gravity_ = gravity;
}


cocos2d::Vec2 PhysicComponent::getGravity()
{
  return gravity_;
}


PhysicComponent* PhysicComponent::clone()
{
  return new PhysicComponent();
}
