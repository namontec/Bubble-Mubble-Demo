#pragma once

class GameObject;

class GraphicComponent
{
public:
  GraphicComponent();
  virtual ~GraphicComponent();

  virtual void update(GameObject& gameObject);
};

