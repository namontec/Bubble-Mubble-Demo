#pragma once

class GameObject;

class PhysicComponent
{
public:
  PhysicComponent();
  virtual ~PhysicComponent();

  virtual void update(GameObject& gameObject, float deltaTime);

};

