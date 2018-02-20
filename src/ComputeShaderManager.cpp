#include "ComputeShaderManager.h"

#include "ComputeShaderUtils.h"

#include <iostream>

//----------------------------------------------------------------------------------------------------------------------

ComputeShaderManager* ComputeShaderManager::m_instance = NULL;

//----------------------------------------------------------------------------------------------------------------------

ComputeShaderManager::ComputeShaderManager()
{
}

//----------------------------------------------------------------------------------------------------------------------

ComputeShaderManager::~ComputeShaderManager()
{
	std::cout<<"~ComputeShaderManager\n";
}

//----------------------------------------------------------------------------------------------------------------------

void ComputeShaderManager::cleanUpAll()
{
	// delete compute shaders
}

//----------------------------------------------------------------------------------------------------------------------

void ComputeShaderManager::createCurvesSSBO(unsigned int &buffer, unsigned int _count)
{
	std::cout<<"creating an SSBO for curves\n";

	if (buffer)
		glDeleteBuffers(1, &buffer);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
	// use glBufferData to allocate all 5*count vec3 or infer from curves object
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

//----------------------------------------------------------------------------------------------------------------------

void ComputeShaderManager::createMeshSSBO(unsigned int &buffer, Mesh &mesh)
{
	std::cout<<"creating an SSBO for mesh\n";

	if (buffer)
		glDeleteBuffers(1, &buffer);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);

	unsigned int faceCount = mesh.m_faces.size();
	std::vector<SSBO_Face> SSBOFaces;

	for (auto face : mesh.m_faces)
	{
		SSBO_Face tempFace;

		for (unsigned int i = 0; i < 3; ++i)
		{
			glm::vec3 pos = mesh.m_vertexPositions[face.pos[i]];
			glm::vec3 norm = mesh.m_vertexNormals[face.normal[i]];
			glm::vec2 uv = mesh.m_vertexUVs[face.uv[i]];

			tempFace.position[i] = glm::vec4(pos, 0.0);
			tempFace.normal[i] = glm::vec4(norm, 0.0);
			tempFace.uv[i] = glm::vec4(uv, 0.0, 0.0);

			// maybe also compute face size?
		}

		SSBOFaces.push_back(tempFace);
	}

	// glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, usage);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

//----------------------------------------------------------------------------------------------------------------------

void ComputeShaderManager::copyCurvesSSBO(unsigned int src, unsigned int &dst)
{
	std::cout<<"copying an SSBO into another\n";
	// first check if dst is a buffer
	// then check if they are equal sized
	// then glCopyBufferSubData
}
