#include "MeshRenderable.h"

MeshRenderable::MeshRenderable()
{
	m_VAO = 0;
	m_VBO = 0;
	m_mesh = Mesh();
}

//----------------------------------------------------------------------------------------------------------------------

MeshRenderable::MeshRenderable(Mesh const &_mesh) : m_mesh(_mesh)
{
	generateVAO();
}

//----------------------------------------------------------------------------------------------------------------------

MeshRenderable::~MeshRenderable()
{
	std::cout<<"~MeshRenderable: deleting VAO\n";
	// deleting VAO
}

//----------------------------------------------------------------------------------------------------------------------

void MeshRenderable::generateVAO()
{
	std::cout<<"generating VAO\n";

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

	if (m_VAO)
		glDeleteVertexArrays(1, &m_VAO);
	if (m_VBO)
		glDeleteBuffers(1, &m_VBO);
	// if (m_EBO)
	// 	glDeleteBuffers(1, &m_EBO)

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	// glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
	// &indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex uv coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);
}

//----------------------------------------------------------------------------------------------------------------------

void MeshRenderable::draw()
{
	std::cout<<"drawing VAO\n";
}
