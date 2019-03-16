#pragma once

#include "cocos2d.h"
#include <string>

class Globals
{
public:
  Globals();
  virtual ~Globals();

public:
  const static cocos2d::Size designResoluton;
  const static int  framesPerSecond;

  const static int timer;

  const static std::string fileNameSpriteSheet;
  const static std::string fileNameBackground;
  const static std::string fileNameAim;
  const static std::string fileNameBomb;
  const static std::string fileNameCannon;
  const static std::string fileNameCannonBall;
  const static std::string fileNameStand;
  const static std::string fileNameTarget;
  const static std::string fileNameClock;


  enum {
    BACKGROUND = -1,
    MIDDLEGROUND = 0,
    FOREGROUND = 1
  };


};

