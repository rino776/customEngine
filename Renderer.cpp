#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Camera.h"

#include <iostream>
#include "Texture.h"


Shader* shader;

Texture* defaultTex;

unsigned int squareVAO;
unsigned int squareEBO;

unsigned int CubeVAO;

const float m_WIDTH = 800;
const float m_HEIGHT = 600;
const float m_DEPTH = 500;

glm::mat4 m_Projection;
glm::mat4 m_Model = glm::mat4(1.0f);
glm::mat4 m_View = glm::mat4(1.0f);

bool m_Perspective = true;

//todo: texture

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

float m_CubeVertices[] = {
       -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  
       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 
       -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  

       -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  
       -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 
       -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,

       -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,

       -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 
       -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,

       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 
       -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f
};

float m_CubeTextureCoords[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,

    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,

    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f

};

float m_cubeNormals[] = {
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,

    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,

    -1.0f,  0.0f,  0.0f,
    - 1.0f,  0.0f,  0.0f,
    - 1.0f,  0.0f,  0.0f,
    - 1.0f,  0.0f,  0.0f,
    - 1.0f,  0.0f,  0.0f,
    - 1.0f,  0.0f,  0.0f,

    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,

    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,

    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f
};

static void createVBO(float vertices[], int size) {

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

}

static unsigned int createEBO(unsigned int indices[], int size) {
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

    return EBO;

}


static void bindAttribs() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Renderer::init() {
    
    shader = new Shader("lightShader.vs","lightShader.fs");

    defaultTex = Texture::loadTexture("default.png");

    //create square array
    glGenVertexArrays(1, &squareVAO);
    glBindVertexArray(squareVAO);

    createVBO(m_squareVertices, sizeof(m_squareVertices));

    squareEBO = createEBO(m_squareIndices, sizeof(m_squareIndices));

    bindAttribs();

    glBindVertexArray(0);


    //create cube array
    glGenVertexArrays(1, &CubeVAO);
    glBindVertexArray(CubeVAO);

    //create vbo for vertices
    createVBO(m_CubeVertices, sizeof(m_CubeVertices));

    //create vertex attrib pointers for vertex and colour
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    //textures
    createVBO(m_CubeTextureCoords, sizeof(m_CubeTextureCoords));
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(2);

    //normals
    createVBO(m_cubeNormals, sizeof(m_cubeNormals));

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);


    if (m_Perspective) {
        m_Projection = glm::perspective((float)glm::radians(45.0f), 800.0f/ 600.0f, 0.01f, 100.0f);
        
    }else {
        m_Projection = glm::ortho(0.0f, m_WIDTH, 0.0f, m_HEIGHT, -1.0f, 1.0f);
    }


 
}

void Renderer::drawSquare(glm::vec3 position,glm::vec3 scale, glm::vec3 rotation) {
    
    shader->use();
    
    //clear the model and view matrices
    m_Model = glm::mat4(1.0f);
    m_View = glm::mat4(1.0f);

    

    //invert the z positional axis
    position.z *= -1;

    m_Model = glm::translate(m_Model, position);
    m_Model = glm::rotate(m_Model, glm::radians(rotation.x), glm::vec3(1.0f,0.0f,0.0f));
    m_Model = glm::rotate(m_Model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_Model = glm::rotate(m_Model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_Model = glm::scale(m_Model, scale);

    shader->setMatrix("model", m_Model);
    shader->setMatrix("view", m_View);
    shader->setMatrix("projection", m_Projection);

  

    glBindVertexArray(squareVAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareEBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

void Renderer::drawCube(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) {
    
    shader->use();

    //clear the model and view matrices
    m_Model = glm::mat4(1.0f);
    m_View = glm::mat4(1.0f);

    m_View = Camera::getTransform();

    //invert the z positional axis
    position.z *= -1;

    m_Model = glm::translate(m_Model, position);
    m_Model = glm::rotate(m_Model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_Model = glm::rotate(m_Model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_Model = glm::rotate(m_Model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_Model = glm::scale(m_Model, scale);

    shader->setMatrix("model", m_Model);
    shader->setMatrix("view", m_View);
    shader->setMatrix("projection", m_Projection);

    shader->setVec3("lightPos", glm::vec3(4, 8, -4));
    shader->setVec3("viewPos", Camera::getPosition());

    defaultTex->bindTexture();

    glBindVertexArray(CubeVAO);

    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

}