#include "Spawner.h"
#include "cocos2d.h"


Spawner::Spawner()
{
}


Spawner::~Spawner()
{
}


void Spawner::addPrototype(GameObject* gameObject, const std::string& name)
{
  prototypes_[name] = std::shared_ptr<GameObject>(gameObject);
}


GameObject* Spawner::spawn(const std::string& byName)
{
  return prototypes_[byName]->clone();
}
