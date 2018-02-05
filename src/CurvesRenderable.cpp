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
	std::vector<glm::vec3> vertices;
	for (auto curve : m_curves.m_curves)
	{
		// push back pairs of vertices since GL_LINES draws 2 vertices at a time
		for (int i = 0; i < 4; ++i)
		{
			vertices.push_back(curve.vertices[i]);
			vertices.push_back(curve.vertices[i + 1]);
		}
	}

	m_indices = vertices.size();

	if (m_VAO)
		glDeleteVertexArrays(1, &m_VAO);
	if (m_VBO)
		glDeleteBuffers(1, &m_VBO);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// check OpenGL error
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
		std::cout << "OpenGL error: " << err << std::endl;

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
	glDrawArrays(GL_LINES, 0, m_indices);
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
