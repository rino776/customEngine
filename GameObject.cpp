#include "GameObject.h"

#include <iostream>




GameObject::GameObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
	GameObject::Position = position;
	GameObject::Rotation = rotation;
	GameObject::Scale = scale;
}

GameObject::GameObject() {
	GameObject::Position = glm::vec3(0.0f,0.0f,0.0f);
	GameObject::Rotation = glm::vec3(0.0f,0.0f,0.0f);
	GameObject::Scale = glm::vec3(1.0f,1.0f,1.0f);
}

void GameObject::addComponent(Component* c) {
	for (Component* comp : Components) {
		if (comp->getID() == c->getID()) {
			//error out
			std::cout << "Error: gameobject already has this object! id: " << c->getID() << std::endl;
			return;
		}
	}
	c->setGameObject((void*) this);
	Components.push_back(c);

}

void GameObject::Init() {
	for (Component* c : Components) {
		c->Init();
		std::cout << c->getID() << std::endl;
	}
}

void GameObject::Update() {
	for (Component* c : Components) {
		c->Update();
	}
}

void GameObject::Render() {
	for (Component* c : Components) {
		c->Render();
		//std::cout << c->getID() << std::endl;
	}
}

Component* GameObject::getComponent(int id) {
	for (Component* c : Components) {
		if (c->getID() == id) {
			return c;
		}
	}
	return NULL;
}

