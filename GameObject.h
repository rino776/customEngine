#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <vector>


class GameObject
{
public:


	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
	
	glm::vec3 getPosition() {
		return Position;
	}

	glm::vec3 getRotation() {
		return Rotation;
	}

	glm::vec3 getScale() {
		return Scale;
	}
	
	GameObject(glm::vec3, glm::vec3, glm::vec3);
	GameObject();

	void addComponent(Component*);

	void Init();

	void Update();

	void Render();
	
	Component* getComponent(int);
protected:
	std::vector<Component*> Components;

};

