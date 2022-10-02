#pragma once
#include "ShaderManager.h"
#include <map>
#include "RenderCommand.h"
class RenderManager
{
public:
    bool generateRenderCommands();
    void executeRenderCommands();
private:
    std::unique_ptr<ShaderManager> m_shaderManager = std::make_unique<ShaderManager>();
    std::map<uint64_t, RenderCommand*> m_renderCommands;
};

