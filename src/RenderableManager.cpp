#include "RenderableManager.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <algorithm>

//----------------------------------------------------------------------------------------------------------------------

RenderableManager* RenderableManager::m_instance = NULL;

//----------------------------------------------------------------------------------------------------------------------

RenderableManager::RenderableManager()
{
	meshShader = Shader("shaders/meshShader_vert.glsl", "shaders/meshShader_frag.glsl");
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
	// std::cout<<"RenderableManager::drawRenderables()\n";

	// // TRY NGL PRIMITIVES HERE???
	// meshShader.use();
	// loadMatricesToShader(meshShader.getID());

	// std::cout<<"camPos: "<<glm::to_string(camPos)<<"\n";
	// std::cout<<"MVP: "<<glm::to_string(MVP)<<"\n";

	for (auto renderable : m_renderables)
	{
		switch(renderable->getType())
		{
			case MESH:
				std::cout<<"MESH draw call\n";
				renderable->generateVAO();
				meshShader.use();
				loadMatricesToShader(meshShader.getID());
				glUniform3fv(glGetUniformLocation(meshShader.getID(), "colour"), 1, glm::value_ptr(glm::vec3(0.0, 1.0, 0.0)));
				renderable->draw();
				break;
			case DEFAULT:
				std::cout<<"DEFAULT draw call\n";
				break;
			default:
				std::cout<<"fall through draw call\n";
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
