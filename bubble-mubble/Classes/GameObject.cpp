#include "GameObject.h"


GameObject::GameObject(GraphicComponent* graphic, PhysicComponent* physic, InputComponent* input, AbstractUpdate* update)
  : graphic_(std::shared_ptr<GraphicComponent>(graphic)),
  physic_(std::shared_ptr<PhysicComponent>(physic)),
  input_(std::shared_ptr<InputComponent>(input)),
  customUpdate_(std::shared_ptr<AbstractUpdate>(update))
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
  AbstractUpdate*   customUpdate = nullptr;

  if (input_) {
    input = input_->clone();
  }

  if (physic_) {
    physic = physic_->clone();
  }

  if (graphic_) {
    graphic = graphic_->clone();
  }

  if (customUpdate_) {
    customUpdate = customUpdate_->clone();
  }

  return new GameObject( graphic, physic, input, customUpdate );
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

  if (customUpdate_) {
    customUpdate_->update(this, deltaTime);
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

std::shared_ptr<GameObject> GameObject::getChild()
{
  return child_;
}

void GameObject::setChild(GameObject* gameObject)
{
  child_ = std::shared_ptr<GameObject>(gameObject);

  bool childNodeAndParentNodeExists = child_->getGraphic() && graphic_;
  if (childNodeAndParentNodeExists) {
    child_->getGraphic()->setParentNode(graphic_->getNode());
  }
}
