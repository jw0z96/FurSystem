#include "RenderableManager.h"

#include "MeshRenderable.h"
#include "CurvesRenderable.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <algorithm>

//----------------------------------------------------------------------------------------------------------------------

RenderableManager* RenderableManager::m_instance = NULL;

//----------------------------------------------------------------------------------------------------------------------

RenderableManager::RenderableManager()
{
	meshShader = Shader("shaders/render/meshShader_vert.glsl", "shaders/render/meshShader_frag.glsl");
	curvesShader = Shader("shaders/render/curvesShader_vert.glsl", "shaders/render/curvesShader_frag.glsl", "shaders/render/curvesShader_geo.glsl");
	curvesRibbonShader = Shader("shaders/render/curvesShader_vert.glsl", "shaders/render/curvesShader_frag.glsl", "shaders/render/curvesRibbonShader_geo.glsl");
}

//----------------------------------------------------------------------------------------------------------------------

RenderableManager::~RenderableManager()
{
	std::cout<<"~RenderableManager\n";
}

//----------------------------------------------------------------------------------------------------------------------

void RenderableManager::cleanUpAll()
{
	meshShader.cleanUp();
	curvesShader.cleanUp();
	curvesRibbonShader.cleanUp();

	for (auto renderable : m_renderables)
	{
		renderable->cleanUp();
	}
}

//----------------------------------------------------------------------------------------------------------------------

void RenderableManager::recompileShaders()
{
	meshShader.cleanUp();
	curvesShader.cleanUp();
	curvesRibbonShader.cleanUp();
	meshShader = Shader("shaders/render/meshShader_vert.glsl", "shaders/render/meshShader_frag.glsl");
	curvesShader = Shader("shaders/render/curvesShader_vert.glsl", "shaders/render/curvesShader_frag.glsl", "shaders/render/curvesShader_geo.glsl");
	curvesRibbonShader = Shader("shaders/render/curvesShader_vert.glsl", "shaders/render/curvesShader_frag.glsl", "shaders/render/curvesRibbonShader_geo.glsl");
}

//----------------------------------------------------------------------------------------------------------------------

void RenderableManager::registerRenderable(std::shared_ptr<Renderable> _renderable)
{
	// add a renderable to the vector providing it does not already exist in the vector
	if (std::find(m_renderables.begin(), m_renderables.end(), _renderable) == m_renderables.end())
		m_renderables.push_back(_renderable);
}

//----------------------------------------------------------------------------------------------------------------------

void RenderableManager::deregisterRenderable(std::shared_ptr<Renderable> _renderable)
{
	m_renderables.erase(std::remove(m_renderables.begin(), m_renderables.end(), _renderable), m_renderables.end());
	std::cout<<"deregistered "<<_renderable<<"\n";
}

//----------------------------------------------------------------------------------------------------------------------

void RenderableManager::cleanupRenderables()
{
	// temporary vector of the renderables to be deleted so we dont remove items
	// from the m_renderables vector as we iterate through it.
	std::vector<std::shared_ptr<Renderable>> renderablesToBeDeleted;

	for (auto renderable : m_renderables)
	{
		if (renderable->getToBeDeleted())
		{
			renderable->cleanUp();
			renderablesToBeDeleted.push_back(renderable);
		}
	}

	for (auto deletedRenderable : renderablesToBeDeleted)
	{
		deregisterRenderable(deletedRenderable);
	}
}

//----------------------------------------------------------------------------------------------------------------------

void RenderableManager::constructRenderables()
{
	for (auto renderable : m_renderables)
	{
		if (!renderable->getConstructed())
			renderable->generate();
	}
}

//----------------------------------------------------------------------------------------------------------------------

void RenderableManager::drawRenderables()
{
	glm::vec3 col;

	for (auto renderable : m_renderables)
	{
		if (renderable->getVisibility())
		{
			switch(renderable->getType())
			{
				case MESH:
					// std::cout<<"MESH draw call\n";
					meshShader.use();
					loadMatricesToShader(meshShader.getID());
					col = std::static_pointer_cast<MeshRenderable>(renderable)->getColour();
					glUniform3fv(glGetUniformLocation(meshShader.getID(), "u_colour"), 1, glm::value_ptr(col));
					renderable->draw();
					break;

				case CURVES:
					// std::cout<<"CURVES draw call\n";
					// curvesShader.use();
					curvesRibbonShader.use();
					// loadMatricesToShader(curvesShader.getID());
					loadMatricesToShader(curvesRibbonShader.getID());
					// auto r = std::static_pointer_cast<CurvesRenderable>(renderable);
					// col = std::static_pointer_cast<CurvesRenderable>(renderable)->getColour();
					glUniform3fv(glGetUniformLocation(curvesRibbonShader.getID(), "u_colour"), 1, glm::value_ptr(std::static_pointer_cast<CurvesRenderable>(renderable)->getColour()));
					// glUniform1ui(glGetUniformLocation(curvesShader.getID(), "u_numIndices"), std::static_pointer_cast<CurvesRenderable>(renderable)->getIndices());
					renderable->draw();
					break;

				case DEFAULT:
					break;

				default:
					std::cout<<"fall through draw call\n";
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------

void RenderableManager::setMatrices(glm::mat4 _M, glm::mat4 _MV, glm::mat4 _MVP, glm::mat3 _normal, glm::vec3 _camPos)
{
	M = _M;
	MV = _MV;
	MVP = _MVP;
	normalMatrix = _normal;
	camPos = _camPos;
}

//----------------------------------------------------------------------------------------------------------------------

void RenderableManager::loadMatricesToShader(GLuint _pid)
{
	glUniformMatrix4fv(glGetUniformLocation(_pid, "M"), 1, false, glm::value_ptr(M));
	glUniformMatrix4fv(glGetUniformLocation(_pid, "MV"), 1, false, glm::value_ptr(MV));
	glUniformMatrix4fv(glGetUniformLocation(_pid, "MVP"), 1, false, glm::value_ptr(MVP));
	glUniformMatrix3fv(glGetUniformLocation(_pid, "normalMatrix"), 1, false, glm::value_ptr(normalMatrix));
	glUniform3fv(glGetUniformLocation(_pid, "camPos"), 1, glm::value_ptr(camPos));
}
