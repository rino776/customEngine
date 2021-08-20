#pragma once
#include <glm/glm.hpp>
class Camera
{
public:
	static void rotateCamera(glm::vec3 rot);
	static void moveCamera(glm::vec3);
	static glm::mat4 getTransform();
	static glm::vec3 getPosition();
	static void moveForward(float speed);
	static void moveRight(float speed);
	static void moveUp(float speed);
	//screen info
	static void setScreenDimentions(int width, int height);
	static glm::vec2 getScreenDimentions();
};

