#pragma once

#include "cocos2d.h"
#include <string>
#include <stdlib.h>

class Globals
{
public:
  Globals();
  virtual ~Globals();

  static int random(int min, int max);

public:
  const static cocos2d::Size designResoluton;
  const static int framesPerSecond;

  static int timer;
  static int CountTarget;
  static int BallSpeed;

  static int NumberOfCannons;

  const static float Gravity;

  const static std::string fileNameSpriteSheet;
  const static std::string fileNameBackground;
  const static std::string fileNameAim;
  const static std::string fileNameBomb;
  const static std::string fileNameCannon;
  const static std::string fileNameCannonBall;
  const static std::string fileNameStand;
  const static std::string fileNameTarget;
  const static std::string fileNameClock;

  const static std::string fileNameSettings;


  enum {
    BACKGROUND = -1,
    MIDDLEGROUND = 0,
    FOREGROUND = 1
  };

  enum {
    NONE,
    CANNONBALL,
    TARGET,
    CANNON
  };

};

