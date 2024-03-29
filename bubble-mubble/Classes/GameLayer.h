#pragma once

#include <list>
#include "cocos2d.h"
#include "GameObject.h"
#include "Canon.h"
#include "Spawner.h"
#include "InputState.h"
#include "Strategy\BallUpdate.h"
#include "Strategy\TargetUpdate.h"
#include "GameOverScene.h"

class GameLayer : public cocos2d::Layer
{
public:
  static cocos2d::Scene* createScene();
  virtual bool init() override;
  CREATE_FUNC(GameLayer);

  void initSprites();
  void startTheGame();

  virtual void update(float deltaTime) override;
  virtual void fixedUpdate(float delatatine);

  void checkBounds(std::shared_ptr<GameObject> gameObject);

  const cocos2d::Vec2 getMousePosition();
  void onMouseMove(cocos2d::Event *event);
  void onMouseDown(cocos2d::Event *event);
  void onMouseUp(cocos2d::Event *event);

  void startTimer(cocos2d::Label* label);

  std::list<std::shared_ptr<GameObject>>* getObjectPool();

private:
  cocos2d::Size screenSize_;
  InputState inputState_;

  int   score_;
  int   timer_;
  bool  isGameOver_;
  int   targetsLast_;

  std::unique_ptr<GameObject> aim_;
  std::unique_ptr<GameObject> background_;
  std::unique_ptr<GameObject> clock_;
  cocos2d::Label*             timerLabel_;

  Spawner spawner_;

  std::list<std::shared_ptr<GameObject>> objectsPool_;

  //fixed update variables
  const float fixedTimePeriod{ 1.0f / 30.0f };
  float fixedTimeCounter{ 0 };


};


