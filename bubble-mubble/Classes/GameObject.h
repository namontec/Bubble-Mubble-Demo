#pragma once

#include <string>
#include <memory>
#include "cocos2d.h"
#include "Components\PhysicComponent.h"
#include "Components\GraphicComponent.h"
#include "Components\TransformComponent.h"

class GameObject
{
public:
  GameObject(const std::string& fileName, float scale);
  virtual ~GameObject();

  cocos2d::Sprite*  getSprite();
  void              setParentNode(cocos2d::Node *parent, int depth = 0);
  cocos2d::Vec2     getPosition();
  void              setPosition(cocos2d::Vec2 position);

  virtual GameObject* clone();
  virtual void      update(float deltaTime);

protected:
  TransformComponent* transform_;
  PhysicComponent*    physic_;
  GraphicComponent*   graphic_;

private:
  cocos2d::Sprite*  sprite_;
  std::string       fileName_;
  float             scale_;

  cocos2d::Vec2     position_; 
  cocos2d::Vec2     velocity_{ cocos2d::Vec2::ZERO };

};

