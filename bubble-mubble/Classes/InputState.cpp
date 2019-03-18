#include "InputState.h"



InputState::InputState()
{
}


InputState::~InputState()
{
}


void InputState::setMousePosition(cocos2d::Vec2 position)
{
  mousePosition_ = position;
}


cocos2d::Vec2 InputState::getMousePosition()
{
  return mousePosition_;
}


void InputState::setMouseDown(bool mouseDown)
{
  mouseDown_ = mouseDown;
}


bool InputState::getMouseDown()
{
  return mouseDown_;
}
