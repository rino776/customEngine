#pragma once
#include "Component.h"
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Texture.h"
#include "GameObject.h"

class Mesh :
    public Component
{

public:

   struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
        glm::vec3 Colour;
   };


    std::vector<Vertex> vertices;
    std::vector <unsigned int> indices;

    Texture* texture;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture* texture);


    //abstract methods from parent
    void Init() override;
    void Update() override;
    void Render() override;
    int getID() override;
    void setGameObject(void*) override;

protected:
    GameObject* Container;

private:

    unsigned int VAO, VBO, EBO;

};

