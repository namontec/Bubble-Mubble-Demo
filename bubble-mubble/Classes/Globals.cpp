#include "Globals.h"

USING_NS_CC;


const Size Globals::designResoluton = Size(1024, 768);
const int Globals::framesPerSecond = 60;

const int Globals::timer = 50;
const int Globals::CountTarget = 20;
const int Globals::BallSpeed = 300;

int Globals::NumberOfCannons = 10;

const float Globals::Gravity = -2.5f;

const std::string Globals::fileNameSpriteSheet  { "sprites.plist" };
const std::string Globals::fileNameBackground   { "background.png" };
const std::string Globals::fileNameAim          { "Aim.png" };
const std::string Globals::fileNameBomb         { "Bomb.png" };
const std::string Globals::fileNameCannon       { "Cannon.png" };
const std::string Globals::fileNameCannonBall   { "Cannonball.png" };
const std::string Globals::fileNameStand        { "Stand.png" };
const std::string Globals::fileNameTarget       { "Target.png" };
const std::string Globals::fileNameClock        { "Clock.png" };


Globals::Globals()
{
}


Globals::~Globals()
{
}




int Globals::random(int min, int max)
{
  return rand() % (max - min + 1) + min;
}
