#pragma once

#include "InputComponent.h"
#include "InputState.h"

class GameObject;

class PlayerInputComponent : public InputComponent
{
public:
  PlayerInputComponent(InputState* inputState);
  virtual ~PlayerInputComponent();

  InputState* getInputState();

  virtual void update(GameObject* gameObject);
  virtual PlayerInputComponent* clone();

private:
  InputState* inputState_;
};

