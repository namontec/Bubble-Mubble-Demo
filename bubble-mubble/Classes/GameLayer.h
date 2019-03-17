#pragma once

#include <list>
#include "cocos2d.h"
#include "GameObject.h"
#include "Canon.h"
#include "Spawner.h"

class GameLayer : public cocos2d::Layer
{
public:
  static cocos2d::Scene* createScene();
  virtual bool init();
  CREATE_FUNC(GameLayer);

  virtual void update(float deltaTime) override;

  const cocos2d::Vec2 getMousePosition();
  void onMouseMove(cocos2d::Event *event);
  void onMouseDown(cocos2d::Event *event);

private:
  cocos2d::Size screenSize_;
  cocos2d::Vec2 mousePosition_;

  int score_;
  int timer_;

  std::unique_ptr<Canon>      cannon_;
  std::unique_ptr<GameObject> aim_;
  std::unique_ptr<GameObject> background_;
  std::unique_ptr<GameObject> clock_;
  std::unique_ptr<GameObject> cannonStand_;

  Spawner spawner_;

  std::list<std::shared_ptr<GameObject>> objectsPool_;
};


