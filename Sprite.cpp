#include "Sprite.h"
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

Sprite::Sprite(Texture* texture) {
	this->texture = texture;
}

Shader* spriteShader;

float m_squareVertices[] = {
	 0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 1.0f,   1.0f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // bottom right
	-0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,   0.0f, 1.0f, // bottom left
	-0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 1.0f,   0.0f, 0.0f // top left
};

unsigned int m_squareIndices[] = {
	0, 1, 3,
	1, 2, 3
};

void Sprite::Init() {

	spriteShader = new Shader("vertex.vs", "fragment.fs");

	//create array and buffer objects
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_squareVertices), m_squareVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_squareIndices), m_squareIndices, GL_STATIC_DRAW);
	
	//bind attributes

	//vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//colour
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Sprite::Update() {
}

void Sprite::Render() {

	spriteShader->use();
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	
	glm::vec2 screenDimentions = Camera::getScreenDimentions();

	glm::mat4 projection = glm::ortho(0.0f, screenDimentions.x,0.0f, screenDimentions.y);	//TODO: set the proper screen dimentions here

	glm::vec3 Position = Container->getPosition();
	glm::vec3 Rotation = Container->getRotation();
	glm::vec3 Scale = Container->getScale();

	//scale position and scale so that they stay the same place and size when the screen changes
	//looks kinda wierd at different resolutions though :/
	Position = Position / glm::vec3(800.0f,600.0f,1.0f);
	Position = Position * glm::vec3(screenDimentions, 0);

	Scale = Scale / glm::vec3(800.0f,600.0f,1.0f);
	Scale = Scale * glm::vec3(screenDimentions, 0);


	model = glm::translate(model, Position);
	model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, Scale);

	spriteShader->setMatrix("model", model);
	spriteShader->setMatrix("view", view);
	spriteShader->setMatrix("projection", projection);



	texture->bindTexture();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


}

int Sprite::getID() {
	return 2;
}

void Sprite::setGameObject(void* container) {
	Sprite::Container = (GameObject*)container;
}
