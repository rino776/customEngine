#include "Texture.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>


Texture::Texture(int id, int width, int height) {
	Texture::m_id = id;
	Texture::m_width = width;
	Texture::m_height = height;
}


Texture* Texture::loadTexture(const char* name) {

	//load image from file
	stbi_set_flip_vertically_on_load(false);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(name, &width, &height, &nrChannels, 0);

	unsigned int id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//generate the actual texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	//free up data
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	return new Texture(id, width, height);

}

void Texture::bindTexture() {
	glBindTexture(GL_TEXTURE_2D, m_id);
}
