#pragma once
#include "AbstractUpdate.h"

class BallUpdate : public AbstractUpdate
{
public:
  BallUpdate();
  virtual ~BallUpdate();

  virtual void update(GameObject* gameObject, float deltaTime) override;

  AbstractUpdate* clone() override;
};

