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

  void        addPrototype(const std::string& name, const std::string& fileName, float scale = 1.0f);
  GameObject* spawn(const std::string& byName);

private:
  std::map<std::string, std::shared_ptr<GameObject>> prototypes_;
};

