#pragma once
#include <GLFW/glfw3.h>
class Time
{
public:

	static double deltaTime;


	static void setDeltaTime(double delta) {
		deltaTime = delta;
	}

	static double getTime() {
		return glfwGetTime();
	}

};

