#pragma once

#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
  static cocos2d::Scene* createScene();
  virtual bool init();
  CREATE_FUNC(GameOverScene);


  static int targetsDestroyed;
  static int targetsTotal;

private:
  cocos2d::Size    screenSize_;

};
