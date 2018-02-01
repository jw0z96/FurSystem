#include "MeshRenderable.h"

MeshRenderable::MeshRenderable()
{
	std::cout<<"MeshRenderable()\n";
	m_VAO = 0;
	m_VBO = 0;
	m_indices = 0;
	m_mesh = Mesh();
}

//----------------------------------------------------------------------------------------------------------------------

MeshRenderable::MeshRenderable(Mesh const &_mesh) : m_mesh(_mesh)
{
	std::cout<<"MeshRenderable(Mesh const &_mesh)\n";
	m_VAO = 0;
	m_VBO = 0;
	m_indices = 0;
	generateVAO();
}

//----------------------------------------------------------------------------------------------------------------------

MeshRenderable::~MeshRenderable()
{
	std::cout<<"~MeshRenderable: deleting VAO\n";
	// // deleting VAO
	// if (m_VAO)
	// 	glDeleteVertexArrays(1, &m_VAO);
	// if (m_VBO)
	// 	glDeleteBuffers(1, &m_VBO);
}

//----------------------------------------------------------------------------------------------------------------------

void MeshRenderable::generateVAO()
{
	std::cout<<"generating VAO\n";

	// std::vector<Vertex> vertices;
	std::vector<glm::vec3> vertices;
	for (auto face : m_mesh.m_faces)
	{
		for (int i = 0; i < 3; ++i)
		{
			glm::vec3 pos = m_mesh.m_vertexPositions[face.pos[i]];
			// glm::vec3 norm = m_mesh.m_vertexNormals[face.normal[i]];
			// glm::vec2 uv = m_mesh.m_vertexUVs[face.uv[i]];
			// vertices.emplace_back(pos, norm, uv);
			vertices.push_back(pos);
		}
	}

	m_indices = vertices.size();

	std::cout<<m_indices<<" indices\n";

	if (m_VAO)
		glDeleteVertexArrays(1, &m_VAO);
	if (m_VBO)
		glDeleteBuffers(1, &m_VBO);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	// glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	// vertex positions
	// glEnableVertexAttribArray(0);
	// glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	// // vertex normals
	// glEnableVertexAttribArray(1);
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// // vertex uv coords
	// glEnableVertexAttribArray(2);
	// glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	glBindVertexArray(m_VAO);

	// check OpenGL error
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error: " << err << std::endl;
    }
	std::cout<<"done\n";
	glBindVertexArray(0);
}

//----------------------------------------------------------------------------------------------------------------------

void MeshRenderable::draw()
{
	std::cout<<"drawing "<<m_indices<<" VAO indices\n";
	glBindVertexArray(m_VAO);
	// check OpenGL error
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error: " << err << std::endl;
    }
	glDrawArrays(GL_TRIANGLES, 0, m_indices);
	glBindVertexArray(0);
}
