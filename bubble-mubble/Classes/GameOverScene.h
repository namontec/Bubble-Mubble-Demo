#pragma once

#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
  static cocos2d::Scene* createScene(int targetsDestroyed, int targetsTotal);
  virtual bool init();
  CREATE_FUNC(GameOverScene);


  int targetsDestroyesd;
  int targetsTotal;

private:
  Label*  labelTitle_;
  Label*  labelDestroyed_;
  Size    screenSize_;

};
