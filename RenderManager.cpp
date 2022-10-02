#include "RenderManager.h"


bool RenderManager::generateRenderCommands() {
	//iterate through all renderables?
	//what part of the code calls this? how are the renderables stored? where are the renderables stored?
	return false; //not implemented yet
}

void RenderManager::executeRenderCommands() {
	for(auto const& [key, command] : m_renderCommands)
	{
		//onBindParameters?
		command->execute();
	}
}
