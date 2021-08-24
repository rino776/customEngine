#include "Mesh.h"
#include <iostream>
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

int Mesh::getID() {
	return 1; //is there some way to dynamically allocate this?
}

void Mesh::setGameObject(void* container) {
	Mesh::Container = (GameObject*)container;
}


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture* texture){
	this->vertices = vertices;
	this->indices = indices;
	this->texture = texture;

}

Shader* shader1;


//will be called per object
void Mesh::Init() {

	shader1 = new Shader("lightShader.vs","lightShader.fs");
	

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//vertex pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	
	//vertex norms
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	
	//texcoords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	//vertex Colour
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Colour));

	glBindVertexArray(0);
}

void Mesh::Update() {

}

void Mesh::Render() {
	//TODO: sort out textures

	shader1->use();

	glm::mat4 model = glm::mat4(1.0);
	glm::mat4 view = Camera::getTransform();
	glm::mat4 projection = glm::perspective((float)glm::radians(45.0f), 800.0f / 600.0f, 0.01f, 100.0f);

	glm::vec3 Position = Container->getPosition();
	glm::vec3 Rotation = Container->getRotation();
	glm::vec3 Scale = Container->getScale();

	model = glm::translate(model, Position);
	model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, Scale);

	shader1->setMatrix("model", model);
	shader1->setMatrix("view", view);
	shader1->setMatrix("projection", projection);
	
	shader1->setVec3("lightPos",glm::vec3(0,1,0));
	shader1->setVec3("viewPos",Camera::getPosition());

	texture->bindTexture();

	//glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


