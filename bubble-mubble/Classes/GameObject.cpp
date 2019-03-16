#include "GameObject.h"



GameObject::GameObject(cocos2d::Sprite* sprite)
  : sprite_(sprite)
{
}


GameObject::~GameObject()
{
}

cocos2d::Sprite * GameObject::getSprite()
{
  return sprite_;
}
