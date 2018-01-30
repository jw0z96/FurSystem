#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <iostream>
#include <vector>

struct Vertex
{
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief constructor
	//----------------------------------------------------------------------------------------------------------------------
	Vertex(glm::vec3 _pos, glm::vec3 _norm, glm::vec2 _uv)
	{
		position = _pos;
		normal = _norm;
		uv = _uv;
	}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief vertex position
	//----------------------------------------------------------------------------------------------------------------------
	glm::vec3 position;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief vertex normal
	//----------------------------------------------------------------------------------------------------------------------
	glm::vec3 normal;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief vertex uv
	//----------------------------------------------------------------------------------------------------------------------
	glm::vec2 uv;
};

struct Face
{
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief vertex indices
	//----------------------------------------------------------------------------------------------------------------------
	unsigned int pos[3];
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief uv indices
	//----------------------------------------------------------------------------------------------------------------------
	unsigned int uv[3];
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief normal indices
	//----------------------------------------------------------------------------------------------------------------------
	unsigned int normal[3];
};

struct Mesh
{
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief constructor
	//----------------------------------------------------------------------------------------------------------------------
	Mesh(){}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief constructor
	//----------------------------------------------------------------------------------------------------------------------
	Mesh(std::vector<glm::vec3>& _pos, std::vector<glm::vec2>& _uv, std::vector<glm::vec3>& _norm, std::vector<Face>& _faces)
	{
		m_vertexPositions = _pos;
		m_vertexNormals = _norm;
		m_vertexUVs = _uv;
		m_faces = _faces;
	}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief m_vertices the vertices that make up the mesh
	//----------------------------------------------------------------------------------------------------------------------
	// std::vector<Vertex> m_vertices;
	std::vector<glm::vec3> m_vertexPositions;
	std::vector<glm::vec3> m_vertexNormals;
	std::vector<glm::vec2> m_vertexUVs;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief m_faces the faces of the mesh, made up of indices
	//----------------------------------------------------------------------------------------------------------------------
	std::vector<Face> m_faces;
};

#endif // MESH_H