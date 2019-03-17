#pragma once

class GameObject;

class InputComponent
{
public:
  InputComponent();
  virtual ~InputComponent();

  virtual void            update(GameObject* gameObject) = 0;
  virtual InputComponent* clone() = 0;
};

