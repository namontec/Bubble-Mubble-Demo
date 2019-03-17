#pragma once
#include "cocos2d.h"

class GameObject;

class GraphicComponent
{
public:
  GraphicComponent(const std::string& fileName);
  virtual ~GraphicComponent();

  cocos2d::Sprite*  getSprite();
  void              setParentNode(cocos2d::Node *parent, int depth = 0);

  void              setPosition(cocos2d::Vec2 position);
  cocos2d::Vec2     getPosition();

  void              setAnchorPoint(cocos2d::Vec2 anchor);
  cocos2d::Vec2     getAnchorPoint();

  void              setScale(float scale);
  float             getScale();

  void              setRotation(float angle);
  float             getRotation();
  
  virtual void update(GameObject* gameObject);

  virtual GraphicComponent* clone();

private:
  cocos2d::Sprite*  sprite_;
  std::string       fileName_;
};

