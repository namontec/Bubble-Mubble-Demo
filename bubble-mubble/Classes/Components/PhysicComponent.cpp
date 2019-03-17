#include "PhysicComponent.h"



PhysicComponent::PhysicComponent()
{
}


PhysicComponent::~PhysicComponent()
{
}


void PhysicComponent::update(GameObject* gameObject, float deltaTime)
{
}

PhysicComponent* PhysicComponent::clone()
{
  return new PhysicComponent();
}
