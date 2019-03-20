#pragma once
class GameObject;

class AbstractUpdate
{
public:
  AbstractUpdate();
  virtual ~AbstractUpdate();

  virtual void update(GameObject* gameObject, float deltaTime) = 0;

  virtual AbstractUpdate* clone() = 0;
};

