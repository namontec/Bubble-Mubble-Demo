#pragma once
class GameComponent
{
public:
  virtual ~GameComponent();

  virtual void update(float deltaTime) = 0;
};

