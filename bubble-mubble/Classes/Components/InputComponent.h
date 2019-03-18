#pragma once

#include "InputState.h"
class GameObject;

class InputComponent
{
public:
  InputComponent();
  virtual ~InputComponent();

  virtual InputState*     getInputState() = 0;

  virtual void            update(GameObject* gameObject) = 0;
  virtual InputComponent* clone() = 0;
};

