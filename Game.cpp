#include "Game.h"
#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include "Time.h"
#include "Camera.h"
#include "Input.h"
#include <iostream>
#include "GameObject.h"
#include "Mesh.h"
#include "Texture.h"
#include "Sprite.h"

/*
	TODO:
		- entity component system (2D and 3D)
			- behaviour
			- collider
			- messaging/share data among components?

		- text rendering
			- multiple shaders/easy shader switching
				-make that part of entity component?
		
		- lights (put as gameobject component?)
			- put into own class
			- attenuation
		- model loading?
		- mouse to world coords
		- documentation
		- config files

*/


//camera variables
float speed = 10;
glm::vec2 lastMouse;
glm::vec2 mouse;


//TODO: move this into a 'primitive' class
float cubeVertices[] = {
	// Back face
	-0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,

	// Front face
	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	// Left face
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	// Right face
	 0.5f,  0.5f,  0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,

	 // Bottom face
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
 	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	// Top face
	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f,

};
float cubeNormals[] = {
	//back
	0.0f,0.0f,1.0f,
	0.0f,0.0f,1.0f, 
	0.0f,0.0f,1.0f, 
	0.0f,0.0f,1.0f, 
	0.0f,0.0f,1.0f, 
	0.0f,0.0f,1.0f, 
	
	//front
	0.0f,0.0f,-1.0f,
	0.0f,0.0f,-1.0f,
	0.0f,0.0f,-1.0f,
	0.0f,0.0f,-1.0f,
	0.0f,0.0f,-1.0f,
	0.0f,0.0f,-1.0f,

	//left
	1.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,

	//right
	-1.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,

	//bottom
	0.0f,-1.0f,0.0f,
	0.0f,-1.0f,0.0f,
	0.0f,-1.0f,0.0f,
	0.0f,-1.0f,0.0f,
	0.0f,-1.0f,0.0f,
	0.0f,-1.0f,0.0f,

	//top
	0.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f
};
float cubeUV[] = { 
	0.0f, 0.0f,// Bottom-left
	1.0f, 1.0f,// top-right
	1.0f, 0.0f,// bottom-right         
	1.0f, 1.0f,// top-right
	0.0f, 0.0f,// bottom-left
	0.0f, 1.0f,// top-left

	0.0f, 0.0f,// bottom-left
	1.0f, 0.0f,// bottom-right
	1.0f, 1.0f,// top-right
	1.0f, 1.0f,// top-right
	0.0f, 1.0f,// top-left
	0.0f, 0.0f, // bottom-left


	1.0f, 0.0f,// top-right
	1.0f, 1.0f,// top-left
	0.0f, 1.0f,// bottom-left
	0.0f, 1.0f,// bottom-left
	0.0f, 0.0f,// bottom-right
	1.0f, 0.0f,// top-right


	1.0f, 0.0f,// top-left
	0.0f, 1.0f,// bottom-right
	1.0f, 1.0f,// top-right         
	0.0f, 1.0f,// bottom-right
	1.0f, 0.0f,// top-left
	0.0f, 0.0f,// bottom-left    


	0.0f, 1.0f, // top-right
	1.0f, 1.0f,// top-left
	1.0f, 0.0f,// bottom-left
	1.0f, 0.0f,// bottom-left
	0.0f, 0.0f,// bottom-right
	0.0f, 1.0f,// top-right


	0.0f, 1.0f,// top-left
	1.0f, 0.0f,// bottom-right
	1.0f, 1.0f,// top-right     
	1.0f, 0.0f,// bottom-right
	0.0f, 1.0f,// top-left
	0.0f, 0.0f,// bottom-left       
};
float cubeColours[] = {
	1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 

	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 

	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 

	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 

	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 

	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f, 
	1.0f,1.0f,1.0f
};

std::vector<Mesh::Vertex> vertices;
std::vector<unsigned int> indices;

Mesh* testMesh;
Mesh* testMesh2;

Sprite* testSprite;

GameObject Test;
GameObject Test2;



void Game::init() {

	Test = GameObject(glm::vec3(400,300,0),glm::vec3(0.0, 0.0, 0.0), glm::vec3(100, 100, 100));

	unsigned int index = 0;
	int UV = 0;

	for (int i = 0; i < 108; i+=3) {
		glm::vec3 pos = glm::vec3(cubeVertices[i], cubeVertices[i + 1], cubeVertices[i + 2]);
		glm::vec3 Normal = glm::vec3(cubeNormals[i], cubeNormals[i + 1], cubeNormals[i + 2]);
		glm::vec2 texCoords = glm::vec2(cubeUV[UV], cubeUV[UV + 1]);
		glm::vec3 Colours = glm::vec3(1.0f, 1.0f, 1.0f);

		vertices.push_back(Mesh::Vertex{ pos, Normal, texCoords, Colours});
		indices.push_back(index);
		index++;
		UV += 2;
	}

	Texture* tex = Texture::loadTexture("default.png");

	testMesh = new Mesh(vertices, indices, tex);
	testMesh2 = new Mesh(vertices, indices, tex);

	testSprite = new Sprite(tex);

	lastMouse = Input::getMousePos();

	Test.addComponent(testSprite);
	Test2.addComponent(testMesh2);

	Test.Init();
	Test2.Init();

	Camera::moveForward(-7);
	Camera::moveUp(2);

}


static void FPSCamera() {
	//basic camera controller
	if (Input::getKeyDown(Input::KEY_W)) {
		Camera::moveForward(speed * Time::deltaTime);
	}
	if (Input::getKeyDown(Input::KEY_S)) {
		Camera::moveForward(-speed * Time::deltaTime);
	}
	if (Input::getKeyDown(Input::KEY_D)) {
		Camera::moveRight(speed * Time::deltaTime);
	}
	if (Input::getKeyDown(Input::KEY_A)) {
		Camera::moveRight(-speed * Time::deltaTime);
	}
	if (Input::getKeyDown(Input::KEY_Q)) {
		Camera::moveUp(speed * Time::deltaTime);
	}
	if (Input::getKeyDown(Input::KEY_E)) {
		Camera::moveUp(-speed * Time::deltaTime);
	}

	mouse = Input::getMousePos();

	double offsetX = mouse.x - lastMouse.x;
	double offsetY = lastMouse.y - mouse.y;

	lastMouse = mouse;

	double sensitivity = 0.2f;
	offsetX *= sensitivity;
	offsetY *= sensitivity;

	Camera::rotateCamera(glm::vec3(offsetY, offsetX, 0.0f));
}

void Game::update() {

	FPSCamera();
	Test.Update();
	Test2.Update();
}

void Game::render() {

	Test.Render();
	Test2.Render();

}