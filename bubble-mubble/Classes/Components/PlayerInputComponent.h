#pragma once

#include "InputComponent.h"

class GameObject;

class PlayerInputComponent : public InputComponent
{
public:
  PlayerInputComponent();
  virtual ~PlayerInputComponent();

  virtual void update(GameObject* gameObject);
  virtual PlayerInputComponent* clone();
};

