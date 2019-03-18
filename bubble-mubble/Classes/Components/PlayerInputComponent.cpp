#include "PlayerInputComponent.h"



PlayerInputComponent::PlayerInputComponent(InputState* inputState)
  : inputState_(inputState)
{
}


PlayerInputComponent::~PlayerInputComponent()
{

}

InputState* PlayerInputComponent::getInputState()
{
  return inputState_;
}


void PlayerInputComponent::update(GameObject * gameObject)
{

}

PlayerInputComponent* PlayerInputComponent::clone()
{
  return new PlayerInputComponent(inputState_);
}
