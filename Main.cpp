
#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "Game.h"
#include "Time.h"
#include "Input.h"
#include "Camera.h"


GLFWwindow* m_window;

const unsigned int HEIGHT = 600;
const unsigned int WIDTH = 800;
const char* TITLE = "Some Title";

void error_callback(int error, const char* desc) {
	fprintf(stderr, "Error: %s\n", desc);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Input::setKey(key, action);
	//TODO: temporary (tm) should expose this somehow to the game...
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	Camera::setScreenDimentions(width, height);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	Input::setMousePos(xpos,ypos);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	Input::setMouseButton(button, action);
}

void init() {
	if (!glfwInit()) {
		std::cout << "GLFW initilization failed! \n";
	}

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window
	m_window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	//initialize it to the correct dimentions
	Camera::setScreenDimentions(WIDTH, HEIGHT);

	if (!m_window) {
		std::cout << "window creation failed!\n";
		glfwTerminate();
	}

	glfwSetKeyCallback(m_window,key_callback);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	glfwSetCursorPosCallback(m_window, cursor_position_callback);
	glfwSetMouseButtonCallback(m_window, mouse_button_callback);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to init GLAD\n";
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glDisable(GL_CULL_FACE);

}

void update() {
	glfwPollEvents();
	glfwSwapBuffers(m_window);
	Game::update();
}

void render() {
	glClearColor(0.1f,0.1f,0.1f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Game::render();
}

int main(int args, char* argv) {

	init();


	glViewport(0, 0, WIDTH, HEIGHT);
	//TODO: input

	Game::init();

	double lastTime = glfwGetTime();
	double currentTime;

	//main loop
	while (!glfwWindowShouldClose(m_window)) {
		//find delta time
		currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		Time::setDeltaTime(deltaTime);

		render();
		update();

	}

	//clean up
	glfwDestroyWindow(m_window);
	glfwTerminate();

	return 0;

}