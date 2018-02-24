#include "CurvesRenderable.h"

#include "ComputeShaderManager.h"

CurvesRenderable::CurvesRenderable()
{
	std::cout<<"CurvesRenderable()\n";
	m_emptyVAO = 0;
	m_SSBO = 0;
	m_curves = Curves();
	m_colour = glm::vec3(1.0, 0.0, 0.0);
}

//----------------------------------------------------------------------------------------------------------------------

CurvesRenderable::~CurvesRenderable()
{
	std::cout<<"~CurvesRenderable "<<this<<"\n";
}

//----------------------------------------------------------------------------------------------------------------------

void CurvesRenderable::generate()
{
	switch (m_curveType)
	{
		case CPU:
			ComputeShaderManager::getInstance()->createCurvesSSBO(m_SSBO, m_curves);
			m_indices = m_curves.m_curves.size();
			break;

		case SSBO:
			ComputeShaderManager::getInstance()->copyCurvesSSBO(m_srcSSBO, m_SSBO);
			// get size of curves buffer
			GLint SSBOSize = 0;
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_SSBO);
			glGetBufferParameteriv(GL_SHADER_STORAGE_BUFFER, GL_BUFFER_SIZE, &SSBOSize);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
			std::cout<<"SSBO size : "<<SSBOSize<<"\n";
			m_indices = SSBOSize / (sizeof(glm::vec4) * 5);
			std::cout<<"m_indices from SSBO size : "<<m_indices<<"\n";
			break;
	}

	if (m_emptyVAO)
		glDeleteVertexArrays(1, &m_emptyVAO);

	// create empty vao for procedural geometry
	glGenVertexArrays(1, &m_emptyVAO);
	glBindVertexArray(m_emptyVAO);
	glBindVertexArray(0);

	isConstructed = true;
}

//----------------------------------------------------------------------------------------------------------------------

void CurvesRenderable::cleanUp()
{
	if (isConstructed)
	{
		std::cout<<"deleting SSBO: "<<m_SSBO<<" and empty VAO: "<<m_emptyVAO<<"\n";

		if (m_SSBO)
			glDeleteBuffers(1, &m_SSBO);
		if (m_emptyVAO)
			glDeleteVertexArrays(1, &m_emptyVAO);

		isConstructed = false;
	}
}

//----------------------------------------------------------------------------------------------------------------------

void CurvesRenderable::draw()
{
	std::cout<<"drawing "<<this<<" & "<<m_indices<<" indices of "<<m_SSBO<<"\n";

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_SSBO);

	glBindVertexArray(m_emptyVAO);
	glDrawArrays(GL_POINTS, 0, m_indices);
	glBindVertexArray(0);

	// check OpenGL error
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
		std::cout << "OpenGL error: " << err << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------

void CurvesRenderable::setSourceSSBO(GLuint _SSBO)
{
	m_srcSSBO = _SSBO;
}

//----------------------------------------------------------------------------------------------------------------------

void CurvesRenderable::setCurveType(CurveType _type)
{
	m_curveType = _type;
}

//----------------------------------------------------------------------------------------------------------------------

void CurvesRenderable::setCurves(Curves const &_curves)
{
	m_curves = _curves;
	isConstructed = false;
}

//----------------------------------------------------------------------------------------------------------------------

void CurvesRenderable::setColour(glm::vec3 const &_col)
{
	m_colour = _col;
}
