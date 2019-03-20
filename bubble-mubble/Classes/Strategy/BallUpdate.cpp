#include "BallUpdate.h"



BallUpdate::BallUpdate()
{
}


BallUpdate::~BallUpdate()
{
}

void BallUpdate::update(GameObject * gameObject, float deltaTime)
{
}

AbstractUpdate * BallUpdate::clone()
{
  return new BallUpdate();
}
