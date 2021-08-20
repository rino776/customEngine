#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer
{
public:
	static void init();
	static void drawSquare(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);
	static void drawCube(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);

};

