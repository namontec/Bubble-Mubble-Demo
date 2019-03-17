#pragma once

class GameObject;

class TransformComponent
{
public:
  TransformComponent();
  virtual ~TransformComponent();

  virtual void update(GameObject& gameObject);
};

