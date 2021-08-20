#pragma once
#include <glm/glm.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader
{
public:
	unsigned int m_ID;

	Shader(const char*, const char*);
	void use();

	void setMatrix(const std::string& name, glm::mat4 value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;

};

