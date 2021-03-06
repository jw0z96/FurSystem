#include "MeshRenderable.h"

MeshRenderable::MeshRenderable()
{
	std::cout<<"MeshRenderable()\n";
	m_VAO = 0;
	m_VBO = 0;
	m_indices = 0;
	m_mesh = Mesh();
	m_colour = glm::vec3(1.0, 0.0, 0.0);
	m_roughness = 0.5;
	m_metallic = 0.5;
}

//----------------------------------------------------------------------------------------------------------------------

MeshRenderable::~MeshRenderable()
{
	std::cout<<"~MeshRenderable "<<this<<"\n";
}

//----------------------------------------------------------------------------------------------------------------------

void MeshRenderable::generate()
{
	std::vector<Vertex> vertices;
	for (auto face : m_mesh.m_faces)
	{
		for (int i = 0; i < 3; ++i)
		{
			glm::vec3 pos = m_mesh.m_vertexPositions[face.pos[i]];
			glm::vec3 norm = m_mesh.m_vertexNormals[face.normal[i]];
			glm::vec2 uv = m_mesh.m_vertexUVs[face.uv[i]];
			vertices.emplace_back(pos, norm, uv);
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
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex uv coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::cout<<"created VAO: "<<m_VAO<<" and VBO: "<<m_VBO<<"\n";
	isConstructed = true;
}

//----------------------------------------------------------------------------------------------------------------------

void MeshRenderable::cleanUp()
{
	if (isConstructed)
	{
		std::cout<<"deleting VAO: "<<m_VAO<<" and VBO: "<<m_VBO<<"\n";
		if (m_VAO)
			glDeleteVertexArrays(1, &m_VAO);
		if (m_VBO)
			glDeleteBuffers(1, &m_VBO);
		isConstructed = false;
	}
}

//----------------------------------------------------------------------------------------------------------------------

void MeshRenderable::draw()
{
	// std::cout<<"drawing "<<this<<" & "<<m_indices<<" VAO indices\n";
	glBindVertexArray(m_VAO);
	// check OpenGL error
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
		std::cout << "OpenGL error: " << err << std::endl;
	glDrawArrays(GL_TRIANGLES, 0, m_indices);
	glBindVertexArray(0);
}

//----------------------------------------------------------------------------------------------------------------------

void MeshRenderable::setMesh(Mesh const &_mesh)
{
	m_mesh = _mesh;
	isConstructed = false;
}

//----------------------------------------------------------------------------------------------------------------------

void MeshRenderable::setColour(glm::vec3 const &_col)
{
	m_colour = _col;
}

//----------------------------------------------------------------------------------------------------------------------

void MeshRenderable::setMetallic(float const &_metallic)
{
	m_metallic = _metallic;
}

//----------------------------------------------------------------------------------------------------------------------

void MeshRenderable::setRoughness(float const &_roughness)
{
	m_roughness = _roughness;
}
