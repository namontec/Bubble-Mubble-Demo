#pragma once

#include <string>
#include "cocos2d.h"

class GameObject
{
public:
  GameObject(const std::string& fileName, float scale);
  virtual ~GameObject();

  cocos2d::Sprite*  getSprite();
  void              setParent(cocos2d::Node *parent, int depth = 0);
  cocos2d::Vec2     getPosition();
  void              setPosition(cocos2d::Vec2 position);

  virtual GameObject* clone();

private:
  cocos2d::Sprite*  sprite_;
  std::string       fileName_;
  float             scale_;
};

