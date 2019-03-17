#pragma once

#include <string>
#include <map>
#include <memory>
#include "Globals.h"
#include "GameObject.h"

class Spawner
{
public:
           Spawner();
  virtual ~Spawner();

  void        addPrototype(GameObject* gameObject, const std::string& name);
  GameObject* spawn(const std::string& byName);

private:
  std::map<std::string, std::shared_ptr<GameObject>> prototypes_;
};

