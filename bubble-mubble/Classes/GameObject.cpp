#include "GameObject.h"


GameObject::GameObject(GraphicComponent* graphic, PhysicComponent* physic, InputComponent* input)
 : graphic_(std::shared_ptr<GraphicComponent>(graphic)),
   physic_ (std::shared_ptr<PhysicComponent>(physic)),
   input_  (std::shared_ptr<InputComponent>(input))
{
}


GameObject::~GameObject()
{

}




GameObject * GameObject::clone()
{
  GraphicComponent* graphic = nullptr;
  PhysicComponent*  physic = nullptr;
  InputComponent*   input = nullptr;

  if (input_) {
    input = input_->clone();
  }

  if (physic_) {
    physic = physic_->clone();
  }

  if (graphic_) {
    graphic = graphic_->clone();
  }

  return new GameObject( graphic, physic, input );
}


void GameObject::update(float deltaTime)
{
  if (input_) {
    input_->update(this);
  }


  if (physic_) {
    physic_->update(this, deltaTime);
  }

  if (graphic_) {
    graphic_->update(this);
  }
}

std::shared_ptr<InputComponent> GameObject::getInput()
{
  return input_;
}

std::shared_ptr<PhysicComponent> GameObject::getPhysic()
{
  return physic_;
}

std::shared_ptr<GraphicComponent> GameObject::getGraphic()
{
  return graphic_;
}
