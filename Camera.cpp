#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

static glm::vec3 m_Position = glm::vec3(0.0f,0.0f,0.0f);
static glm::vec3 m_Front = glm::vec3(0.0f,0.0f,-1.0f);
static glm::vec3 m_Up = glm::vec3(0.0f, 1.0f,0.0f);
static glm::vec3 m_WorldUp = glm::vec3(0.0f, 1.0f,0.0f);
static glm::vec3 m_Right = glm::vec3(1.0f, 0.0f,0.0f);

static glm::vec2 m_screenDimentions = glm::vec2(0.0);

float yaw;
float pitch;

void Camera::rotateCamera(glm::vec3 rot) {
	//yaw = y, pitch = x, roll = z
	yaw += rot.y;
	pitch += rot.x;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	m_Front.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	m_Front.y = sin(glm::radians(pitch));
	m_Front.z = -cos(glm::radians(yaw)) * cos(glm::radians(pitch));

}

void Camera::moveCamera(glm::vec3 pos) {
	m_Position = pos;
}

 glm::mat4 Camera::getTransform() {

	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

 glm::vec3 Camera::getPosition() {
	 return m_Position;
 }

 void Camera::moveForward(float speed) {
	 m_Position += speed * m_Front;
 }

 void Camera::moveRight(float speed) {
	 m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * speed;
 }

 void Camera::moveUp(float speed) {
	 m_Position += speed * m_Up;
 }

 void Camera::setScreenDimentions(int width, int height) {
	 m_screenDimentions = glm::vec2(width, height);
 }

 glm::vec2 Camera::getScreenDimentions() {
	 return m_screenDimentions;
 }

