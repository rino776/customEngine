#pragma once
#include <vector>
#include "Shader.h"
class RenderCommand
{
public:
    RenderCommand(std::vector<float> vertices, std::vector<uint32_t> indices);

    void execute();
    virtual ~RenderCommand();

protected:
    void onBindParameters(Shader* shader);

private:
    //TODO: Geometry, Renderable

    uint32_t m_VAO;
    uint32_t m_VBO;
    uint32_t m_EBO;
    uint32_t m_indicesSize;
};

