#include "RenderableManager.h"

#include <iostream>
#include <algorithm>

//----------------------------------------------------------------------------------------------------------------------

RenderableManager* RenderableManager::m_instance = NULL;

//----------------------------------------------------------------------------------------------------------------------

RenderableManager::RenderableManager()
{
}

//----------------------------------------------------------------------------------------------------------------------

RenderableManager::~RenderableManager()
{
	std::cout<<"~RenderableManager\n";
}

//----------------------------------------------------------------------------------------------------------------------

void RenderableManager::registerRenderable(std::shared_ptr<Renderable> _renderable)
{
	m_renderables.push_back(_renderable);
}

//----------------------------------------------------------------------------------------------------------------------

void RenderableManager::deregisterRenderable(std::shared_ptr<Renderable> _renderable)
{
	m_renderables.erase(std::remove(m_renderables.begin(), m_renderables.end(), _renderable), m_renderables.end());
}

//----------------------------------------------------------------------------------------------------------------------

void RenderableManager::drawRenderables()
{
	for (auto renderable : m_renderables)
		renderable->draw();
}
