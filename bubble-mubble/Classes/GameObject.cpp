#include "GameObject.h"



GameObject::GameObject(const std::string& fileName, float scale)
  : fileName_(fileName), scale_(scale)
{
  sprite_ = cocos2d::Sprite::createWithSpriteFrameName(fileName_);
  sprite_->setScale(scale_);
  sprite_->retain();
}

GameObject::~GameObject()
{
  sprite_->release();
}

cocos2d::Sprite * GameObject::getSprite()
{
  return sprite_;
}


void GameObject::setParentNode(cocos2d::Node *parent, int depth)
{
  parent->addChild(sprite_, depth);
}


cocos2d::Vec2 GameObject::getPosition()
{
  return sprite_->getPosition();
}


void GameObject::setPosition(cocos2d::Vec2 position)
{
  sprite_->setPosition(position);
}


GameObject * GameObject::clone()
{
  return new GameObject(fileName_, scale_);
}
