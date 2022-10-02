#include "ShaderManager.h"

ShaderManager::ShaderManager() 
{
    m_shaders.insert(std::make_pair<std::string, Shader*>("Basic", new Shader("vertex.vs", "fragment.fs")));
    m_shaders.insert(std::make_pair<std::string, Shader*>("Light", new Shader("lightShader.vs", "lightShader.fs")));
}

Shader* ShaderManager::find(std::string name)
{    
    auto shader = m_shaders.find(name);
    
    if (shader != m_shaders.end()) {
        return shader->second;
    }
    
    return nullptr;
}