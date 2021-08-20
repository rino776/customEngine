#include "GameObject.h"
#include <vector>
#include <iostream>

std::vector<Component*> Components;


void GameObject::addComponent(Component* c) {
	for (Component* comp : Components) {
		if (comp->getID() == c->getID()) {
			//error out
			std::cout << "Error: gameobject already has this object! id: " << c->getID() << std::endl;
			return;
		}
	}

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

