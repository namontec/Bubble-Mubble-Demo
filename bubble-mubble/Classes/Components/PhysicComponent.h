#pragma once

#include "GameObject.h"
#include "Component.h"

class PhysicComponent : pubic Component
{
public:
  PhysicComponent(GameObject* gameObject);
  virtual ~PhysicComponent();

  virtual void update(float deltaTime) override;

};

