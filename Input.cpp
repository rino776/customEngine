#include "Input.h"
#include "Camera.h"

//TODO: get mouse as clip?
//get mouse as world?


glm::vec2 m_mousePos = glm::vec2(0.0f);


static int m_Keys[512] = { 0 };

static int m_Buttons[8] = { 0 };

void Input::setKey(int key, int action) {
	m_Keys[key] = action;
}

int Input::getKey(int key) {
	return m_Keys[key];
}

bool Input::getKeyDown(int key) {
	return (m_Keys[key] == Input::PRESS || m_Keys[key] == Input::REPEAT);
}

void Input::setMousePos(double xpos, double ypos) {
	m_mousePos = glm::vec2(xpos, ypos);

}

glm::vec2 Input::getMousePos() {
	return m_mousePos;
}

glm::vec2 Input::getMouseClipPos()
{
	glm::vec2 screenDimentions = Camera::getScreenDimentions();

	double x = 2 * ((float)m_mousePos.x / (float)screenDimentions.x) - 1;
	double y = 2 * ((float)m_mousePos.y / (float)screenDimentions.y) - 1;
	

	return glm::vec2(x,-y);
}

void Input::setMouseButton(int button, int action)
{
	m_Buttons[button] = action;
}

bool Input::getMouseButton(int button, int action)
{
	return m_Buttons[button] == action;
}


