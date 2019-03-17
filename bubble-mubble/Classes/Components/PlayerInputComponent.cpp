#include "PlayerInputComponent.h"



PlayerInputComponent::PlayerInputComponent()
{
}


PlayerInputComponent::~PlayerInputComponent()
{

}


void PlayerInputComponent::update(GameObject * gameObject)
{

}

PlayerInputComponent* PlayerInputComponent::clone()
{
  return new PlayerInputComponent();
}
