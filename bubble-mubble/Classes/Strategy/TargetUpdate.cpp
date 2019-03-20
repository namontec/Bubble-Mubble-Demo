#include "TargetUpdate.h"



TargetUpdate::TargetUpdate()
{
}


TargetUpdate::~TargetUpdate()
{
}

void TargetUpdate::update(GameObject * gameObject, float deltaTime)
{
}

AbstractUpdate * TargetUpdate::clone()
{
  return new TargetUpdate();
}
