#include "GraphicComponent.h"



GraphicComponent::GraphicComponent()
{
  //create empty node
  node_ = cocos2d::Node::create();
  node_->retain();
}

GraphicComponent::GraphicComponent(const std::string& fileName)
   : fileName_(fileName)
{

    node_ = cocos2d::Sprite::createWithSpriteFrameName(fileName_);
    node_->retain();
}


GraphicComponent::~GraphicComponent()
{
  bool spriteHasParent = node_->getParent() != nullptr;
  if (spriteHasParent)
  {
    node_->removeFromParent();
  }

  node_->release();
}



cocos2d::Node * GraphicComponent::getNode()
{
  return node_;
}


void GraphicComponent::setParentNode(cocos2d::Node *parent, int depth)
{
  parent->addChild(node_, depth);
}


void GraphicComponent::setPosition(cocos2d::Vec2 position)
{
  node_->setPosition(position);
}


cocos2d::Vec2 GraphicComponent::getPosition()
{
  return node_->getPosition();
}


void GraphicComponent::setAnchorPoint(cocos2d::Vec2 anchor)
{
  node_->setAnchorPoint(anchor);
}


cocos2d::Vec2 GraphicComponent::getAnchorPoint()
{
  return node_->getAnchorPoint();
}


void GraphicComponent::setScale(float scale)
{
  node_->setScale(scale);
}


float GraphicComponent::getScale()
{
  return node_->getScale();
}


void GraphicComponent::setRotation(float angle)
{
  node_->setRotation(angle);
}


float GraphicComponent::getRotation()
{
  return node_->getRotation();
}

void GraphicComponent::setColor(cocos2d::Color3B color)
{
  node_->setColor(color);
}

cocos2d::Color3B GraphicComponent::getColor()
{
  return node_->getColor();
}


void GraphicComponent::update(GameObject* gameObject)
{
  
}


GraphicComponent * GraphicComponent::clone()
{
  GraphicComponent* component;

  bool hasFileName = !fileName_.empty();
  if (hasFileName) {
    component = new GraphicComponent(fileName_);
  }
  else {
    component = new GraphicComponent();
  }

  component->setScale(getScale());
  component->setRotation(getRotation());
  component->setAnchorPoint(getAnchorPoint());
  component->setPosition(getPosition());
  component->setColor(getColor());

  return component;
}
