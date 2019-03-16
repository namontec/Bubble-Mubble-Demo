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

  const static std::string fileNameSpriteSheet;
  const static std::string fileNameBackground;
  const static std::string fileNameAim;
  const static std::string fileNameBomb;
  const static std::string fileNameCannon;
  const static std::string fileNameCannonBall;
  const static std::string fileNameStand;
  const static std::string fileNameTarge;
  const static std::string fileNameCLock;

};

