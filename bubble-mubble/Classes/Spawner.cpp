#include "Spawner.h"
#include "cocos2d.h"


Spawner::Spawner()
{
}


Spawner::~Spawner()
{
}


void Spawner::addPrototype(const std::string& name, const std::string& fileName, float scale)
{
  prototypes_[name] = std::make_shared<GameObject>(fileName, scale);
}


GameObject* Spawner::spawn(const std::string& byName)
{
  return prototypes_[byName]->clone();
}
