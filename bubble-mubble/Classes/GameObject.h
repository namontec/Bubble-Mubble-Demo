#pragma once

#include "cocos2d.h"

class GameObject
{
public:
  GameObject();
  virtual ~GameObject();

protected:
  cocos2d::Sprite* sprite_;
};

