#pragma once
#include "Component.h"


class GameObject
{
public:

	void addComponent(Component*);

	void Init();

	void Update();

	void Render();
	
	Component* getComponent(int);

};

