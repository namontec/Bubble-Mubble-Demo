#pragma once

#include "cocos2d.h"
#include "GameObject.h"

class GameLayer : public cocos2d::Layer
{
public:
  static cocos2d::Scene* createScene();
  virtual bool init();
  CREATE_FUNC(GameLayer);

  virtual void update(float deltaTime) override;

  cocos2d::Vec2 getMousePosition();
  void onMouseMove(cocos2d::Event *event);
  void onMouseDown(cocos2d::Event *event);

private:
  cocos2d::Size screenSize_;
  cocos2d::Vec2 mousePosition_;

  GameObject* cannon_;
};


