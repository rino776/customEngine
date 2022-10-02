#pragma once
#include <unordered_map>
#include "Shader.h"
#include <memory>
class ShaderManager
{
public:
    ShaderManager();

    Shader* find(std::string);

private:
    std::unordered_map<std::string, Shader*> m_shaders;
};

