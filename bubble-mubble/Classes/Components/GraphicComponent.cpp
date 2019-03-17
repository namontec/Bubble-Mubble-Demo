#include "GraphicComponent.h"



GraphicComponent::GraphicComponent(const std::string& fileName)
   : fileName_(fileName)
{

    sprite_ = cocos2d::Sprite::createWithSpriteFrameName(fileName_);
    sprite_->retain();
}


GraphicComponent::~GraphicComponent()
{
  sprite_->release();
}



cocos2d::Sprite * GraphicComponent::getSprite()
{
  return sprite_;
}


void GraphicComponent::setParentNode(cocos2d::Node *parent, int depth)
{
  parent->addChild(sprite_, depth);
}


void GraphicComponent::setPosition(cocos2d::Vec2 position)
{
  sprite_->setPosition(position);
}


cocos2d::Vec2 GraphicComponent::getPosition()
{
  return sprite_->getPosition();
}


void GraphicComponent::setAnchorPoint(cocos2d::Vec2 anchor)
{
  sprite_->setAnchorPoint(anchor);
}


cocos2d::Vec2 GraphicComponent::getAnchorPoint()
{
  return sprite_->getAnchorPoint();
}


void GraphicComponent::setScale(float scale)
{
  sprite_->setScale(scale);
}


float GraphicComponent::getScale()
{
  return sprite_->getScale();
}

void GraphicComponent::setRotation(float angle)
{
  sprite_->setRotation(angle);
}

float GraphicComponent::getRotation()
{
  return sprite_->getRotation();
}


void GraphicComponent::update(GameObject* gameObject)
{
}


GraphicComponent * GraphicComponent::clone()
{
  auto gameObject = new GraphicComponent(fileName_);
  gameObject->setScale(getScale());
  gameObject->setRotation(getRotation());
  gameObject->setAnchorPoint(getAnchorPoint());
  gameObject->setPosition(getPosition());

  return gameObject;
}
