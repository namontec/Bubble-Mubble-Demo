#pragma once

#include <string>
#include <memory>
#include "cocos2d.h"
#include "Globals.h"
#include "Components\PhysicComponent.h"
#include "Components\GraphicComponent.h"
#include "Components\InputComponent.h"
#include "Components\PlayerInputComponent.h"
#include "Strategy\AbstractUpdate.h"


class GameObject
{
public:
  GameObject( GraphicComponent* graphic = nullptr, 
              PhysicComponent*  physic = nullptr, 
              InputComponent*   input = nullptr,
              AbstractUpdate*   update = nullptr );

  virtual ~GameObject();

  virtual GameObject*  clone();
  virtual void        update(float deltaTime);
  virtual void   fixedUpdate(float deltaTime);
  
  bool intersectsObject(std::shared_ptr<GameObject> gameObject);

  std::shared_ptr  <InputComponent> getInput();
  std::shared_ptr <PhysicComponent> getPhysic();
  std::shared_ptr<GraphicComponent> getGraphic();

  std::shared_ptr<GameObject>       getChild();
  void setChild(GameObject* gameObject);

  void setTag(int tag);
  int  getTag();

  bool  isReadyToDie{ false };

protected:
  std::shared_ptr  <InputComponent> input_;
  std::shared_ptr <PhysicComponent> physic_;
  std::shared_ptr<GraphicComponent> graphic_;
  std::shared_ptr<AbstractUpdate>   customUpdate_;

  std::shared_ptr<GameObject>       child_;

  int tag_{ Globals::NONE };

};

