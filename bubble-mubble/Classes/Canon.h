#pragma once

#include "GameObject.h"
#include "Spawner.h"

class Canon : public GameObject
{
public:
  Canon(Spawner* spawner, 
    const std::string& ballName,
    std::list<std::shared_ptr<GameObject>> *objectsPool,
    cocos2d::Node* parentNode_,
    GraphicComponent* graphic = nullptr, 
    PhysicComponent* physic = nullptr, 
    InputComponent* input = nullptr);

  virtual ~Canon();

  void  setRotationToVector(const cocos2d::Vec2 toVector);
  void  setRotation(float angle);
  float getRotation();

  void fireCanon(cocos2d::Vec2 direction);

  virtual GameObject* clone() override;
  virtual void update(float deltatime) override;

private:
  Spawner* spawner_;
  std::string ballName_;
  std::list<std::shared_ptr<GameObject>> *objectsPool_;
  cocos2d::Node* parentNode_;

  float coolTimeInterval = 0.5f;
  float coolTimer{0};
};

