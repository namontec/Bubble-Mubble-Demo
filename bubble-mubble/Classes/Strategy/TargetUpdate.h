#pragma once
#include "AbstractUpdate.h"

class TargetUpdate : public AbstractUpdate
{
public:
  TargetUpdate();
  virtual ~TargetUpdate();

  virtual void update(GameObject* gameObject, float deltaTime) override;

  AbstractUpdate* clone();
};

