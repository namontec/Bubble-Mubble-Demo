#pragma once

#include "cocos2d.h"

class InputState
{
public:
  InputState();
  virtual ~InputState();

  void          setMousePosition(cocos2d::Vec2 position);
  cocos2d::Vec2 getMousePosition();
  void          setMouseDown(bool mouseDown);
  bool          getMouseDown();

private:
  cocos2d::Vec2 mousePosition_;
  bool          mouseDown_;
};

