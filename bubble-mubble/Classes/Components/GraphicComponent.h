#pragma once
#include "cocos2d.h"

class GameObject;

class GraphicComponent
{
public:
  GraphicComponent();
  GraphicComponent(const std::string& fileName);
  virtual ~GraphicComponent();

  cocos2d::Node*  getNode();
  void            setParentNode(cocos2d::Node *parent, int depth = 0);

  void            setPosition(cocos2d::Vec2 position);
  cocos2d::Vec2   getPosition();

  void            setAnchorPoint(cocos2d::Vec2 anchor);
  cocos2d::Vec2   getAnchorPoint();

  void            setScale(float scale);
  float           getScale();

  void            setRotation(float angle);
  float           getRotation();

  void             setColor(cocos2d::Color3B color);
  cocos2d::Color3B getColor();
  
  virtual void update(GameObject* gameObject);

  virtual GraphicComponent* clone();

private:
  cocos2d::Node*  node_;
  std::string     fileName_;
};

