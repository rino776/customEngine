#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Input
{
public:



	static void setKey(int key, int action);
	static int getKey(int key);
	static bool getKeyDown(int key);

	static void setMousePos(double xpos, double ypos);
	static glm::vec2 getMousePos();
	static glm::vec2 getMouseClipPos();

	static void setMouseButton(int button, int action);
	static bool getMouseButton(int button, int action);
	


	static const int PRESS = GLFW_PRESS;
	static const int RELEASE = GLFW_RELEASE;
	static const int REPEAT = GLFW_REPEAT;

	//add to this as needed

	static const int KEY_W = GLFW_KEY_W;
	static const int KEY_S = GLFW_KEY_S;
	static const int KEY_A = GLFW_KEY_A;
	static const int KEY_D = GLFW_KEY_D;
	static const int KEY_Q = GLFW_KEY_Q;
	static const int KEY_E = GLFW_KEY_E;

};

