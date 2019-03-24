#include "Globals.h"

USING_NS_CC;


const Size Globals::designResoluton = Size(1024, 768);
const int Globals::framesPerSecond = 60;

int Globals::timer = 50;
int Globals::CountTarget = 20;
int Globals::BallSpeed = 300;
int Globals::NumberOfCannons = 1;

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

const std::string Globals::fileNameSettings     { "input.txt" };


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
