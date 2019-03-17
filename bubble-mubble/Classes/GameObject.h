#pragma once

#include <string>
#include <memory>
#include "cocos2d.h"
#include "Components\PhysicComponent.h"
#include "Components\GraphicComponent.h"
#include "Components\InputComponent.h"
#include "Components\PlayerInputComponent.h"

class GameObject
{
public:
  GameObject(GraphicComponent* graphic = nullptr, PhysicComponent* physic = nullptr, InputComponent* input = nullptr);
  virtual ~GameObject();

  virtual GameObject* clone();
  virtual void        update(float deltaTime);

  std::shared_ptr  <InputComponent> getInput();
  std::shared_ptr <PhysicComponent> getPhysic();
  std::shared_ptr<GraphicComponent> getGraphic();

protected:
  std::shared_ptr  <InputComponent> input_;
  std::shared_ptr <PhysicComponent> physic_;
  std::shared_ptr<GraphicComponent> graphic_;

private:
  cocos2d::Vec2     position_; 
  cocos2d::Vec2     velocity_{ cocos2d::Vec2::ZERO };

};

