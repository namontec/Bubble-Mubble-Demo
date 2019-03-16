#pragma once

#include "cocos2d.h"

class GameLayer : public cocos2d::Layer
{
public:
  static cocos2d::Scene* createScene();
  virtual bool init();
  CREATE_FUNC(GameLayer);

private:
  cocos2d::Size screenSize_;
};


