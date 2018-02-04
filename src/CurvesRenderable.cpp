#include "CurvesRenderable.h"

CurvesRenderable::CurvesRenderable()
{
	std::cout<<"CurvesRenderable()\n";
	m_VAO = 0;
	m_VBO = 0;
	m_curves = Curves();
	m_colour = glm::vec3(1.0, 0.0, 0.0);
}

//----------------------------------------------------------------------------------------------------------------------

CurvesRenderable::~CurvesRenderable()
{
	std::cout<<"~CurvesRenderable "<<this<<"\n";
}

//----------------------------------------------------------------------------------------------------------------------

void CurvesRenderable::generateVAO()
{
	std::cout<<"generating VAO\n";

	if (m_VAO)
		glDeleteVertexArrays(1, &m_VAO);
	if (m_VBO)
		glDeleteBuffers(1, &m_VBO);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::cout<<"created VAO: "<<m_VAO<<" and VBO: "<<m_VBO<<"\n";
	isVAOConstructed = true;
}

//----------------------------------------------------------------------------------------------------------------------

void CurvesRenderable::cleanupVAO()
{
	if (isVAOConstructed)
	{
		std::cout<<"deleting VAO: "<<m_VAO<<" and VBO: "<<m_VBO<<"\n";
		if (m_VAO)
			glDeleteVertexArrays(1, &m_VAO);
		if (m_VBO)
			glDeleteBuffers(1, &m_VBO);
		isVAOConstructed = false;
	}
}

//----------------------------------------------------------------------------------------------------------------------

void CurvesRenderable::draw()
{
	// std::cout<<"drawing "<<this<<" & "<<m_indices<<" VAO indices\n";
	glBindVertexArray(m_VAO);
	// check OpenGL error
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
		std::cout << "OpenGL error: " << err << std::endl;
	glDrawArrays(GL_LINES, 0, 1);
	glBindVertexArray(0);
}

//----------------------------------------------------------------------------------------------------------------------

void CurvesRenderable::setCurves(Curves const &_curves)
{
	m_curves = _curves;
	isVAOConstructed = false;
}

//----------------------------------------------------------------------------------------------------------------------

void CurvesRenderable::setColour(glm::vec3 const &_col)
{
	m_colour = _col;
}
