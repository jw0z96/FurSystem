#include "ComputeShaderManager.h"

#include "ComputeShaderUtils.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

//----------------------------------------------------------------------------------------------------------------------

ComputeShaderManager* ComputeShaderManager::m_instance = NULL;

//----------------------------------------------------------------------------------------------------------------------

ComputeShaderManager::ComputeShaderManager()
{
	randomDistributionShader = Shader("shaders/compute/randomDistributionShader_comp.glsl");
	bendCurvesShader = Shader("shaders/compute/bendCurvesShader_comp.glsl");
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
	randomDistributionShader.cleanUp();
}

//----------------------------------------------------------------------------------------------------------------------

void ComputeShaderManager::recompileShaders()
{
	cleanUpAll();
	randomDistributionShader = Shader("shaders/compute/randomDistributionShader_comp.glsl");
	bendCurvesShader = Shader("shaders/compute/bendCurvesShader_comp.glsl");
}

//----------------------------------------------------------------------------------------------------------------------

void ComputeShaderManager::createCurvesSSBO(unsigned int &buffer, Curves _curves)
{
	std::cout<<"creating an SSBO for curves\n";

	if (buffer)
		glDeleteBuffers(1, &buffer);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);

	std::vector<glm::vec4> curvesData;
	for (auto curve : _curves.m_curves)
	{
		for (int i = 0; i < 5; ++i)
		{
			curvesData.push_back(glm::vec4(curve.vertices[i], 0.0));
		}
	}
	// use glBufferData to allocate all 5*count vec3 or infer from curves object
	glBufferData(GL_SHADER_STORAGE_BUFFER, curvesData.size() * sizeof(glm::vec4(0.0)), &curvesData[0], GL_DYNAMIC_COPY);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

//----------------------------------------------------------------------------------------------------------------------

// void ComputeShaderManager::createCurvesSSBO(unsigned int &buffer, unsigned int _count)
// {
// 	std::cout<<"creating an SSBO for curves\n";

// 	if (buffer)
// 		glDeleteBuffers(1, &buffer);

// 	glGenBuffers(1, &buffer);
// 	glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
// 	// use glBufferData to allocate all 5*count vec3 or infer from curves object
// 	// TODO: don't init with NULL
// 	glBufferData(GL_SHADER_STORAGE_BUFFER, 5 * _count * sizeof(glm::vec4(0.0)), NULL, GL_DYNAMIC_COPY);
// 	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
// }

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

		glm::vec3 e1 = glm::vec3(tempFace.position[1] - tempFace.position[0]);
		glm::vec3 e2 = glm::vec3(tempFace.position[2] - tempFace.position[0]);
		glm::vec3 e3 = cross(e1, e2);

		tempFace.area = 0.5 * sqrt(e3.x * e3.x + e3.y * e3.y + e3.z * e3.z);

		SSBOFaces.push_back(tempFace);
	}

	glBufferData(GL_SHADER_STORAGE_BUFFER, faceCount * sizeof(SSBO_Face), &SSBOFaces[0], GL_DYNAMIC_COPY);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

//----------------------------------------------------------------------------------------------------------------------

void ComputeShaderManager::copyCurvesSSBO(unsigned int src, unsigned int &dst)
{
	std::cout<<"copying an SSBO into another: "<<src<<" to "<<dst<<"\n";
	// get size of src buffer
	GLint srcBufferSize = 0;
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, src);
	glGetBufferParameteriv(GL_SHADER_STORAGE_BUFFER, GL_BUFFER_SIZE, &srcBufferSize);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	std::cout<<"src buffer size : "<<srcBufferSize<<"\n";

	// first check if dst is a buffer and if they are equal sized
	// if dst buffer exist check if buffers are equal size
	// if not true deleteBuffer and gen with new size
	// if not dst, gen new buffer with new size
	if (dst)
	{
		// get size of dst buffer
		GLint dstBufferSize = 0;
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, dst);
		glGetBufferParameteriv(GL_SHADER_STORAGE_BUFFER, GL_BUFFER_SIZE, &dstBufferSize);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		if (dstBufferSize != srcBufferSize)
		{
			glDeleteBuffers(1, &dst);
			glGenBuffers(1, &dst);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, dst);
			glBufferData(GL_SHADER_STORAGE_BUFFER, srcBufferSize, NULL, GL_DYNAMIC_COPY);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		}
	}
	else
	{
		glGenBuffers(1, &dst);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, dst);
		glBufferData(GL_SHADER_STORAGE_BUFFER, srcBufferSize, NULL, GL_DYNAMIC_COPY);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	// then glCopyBufferSubData
	glBindBuffer(GL_COPY_READ_BUFFER, src);
	glBindBuffer(GL_COPY_WRITE_BUFFER, dst);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, srcBufferSize);
	glBindBuffer(GL_COPY_READ_BUFFER, 0);
	glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

	GLint newBufferSize = 0;
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, dst);
	glGetBufferParameteriv(GL_SHADER_STORAGE_BUFFER, GL_BUFFER_SIZE, &newBufferSize);
	std::cout<<"dst buffer size after copy : "<<newBufferSize<<"\n";
	std::cout<<"dst after copy : "<<dst<<"\n";
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

//----------------------------------------------------------------------------------------------------------------------

void ComputeShaderManager::randomDistribution(unsigned int &meshSSBO, unsigned int &curvesSSBO, unsigned int curveCount, unsigned int faceCount, float meshArea, float length)
{
	// if the SSBO exists, delete it (we need to resize it anyway)
	if (curvesSSBO)
		glDeleteBuffers(1, &curvesSSBO);

	// create a new buffer for the curves
	glGenBuffers(1, &curvesSSBO);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, curvesSSBO);
	std::vector<glm::vec4> curvesData;
	for (unsigned int i = 0; i < (curveCount * 5); ++i)
		curvesData.push_back(glm::vec4(0.0));
	glBufferData(GL_SHADER_STORAGE_BUFFER, curveCount * 5 * sizeof(glm::vec4), &curvesData[0], GL_DYNAMIC_COPY);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	// use shader & send uniforms
	randomDistributionShader.use();
	glUniform1f(glGetUniformLocation(randomDistributionShader.getID(), "u_meshArea"), meshArea);
	glUniform1ui(glGetUniformLocation(randomDistributionShader.getID(), "u_curveCount"), curveCount);
	glUniform1ui(glGetUniformLocation(randomDistributionShader.getID(), "u_faceCount"), faceCount);
	glUniform1f(glGetUniformLocation(randomDistributionShader.getID(), "u_length"), length);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, meshSSBO);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, curvesSSBO);

	// int work_grp_cnt;
	// glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_grp_cnt);
	// glDispatchCompute(work_grp_cnt, 1, 1);
	glDispatchCompute((int(curveCount) / 128) + 1, 1, 1);
}

//----------------------------------------------------------------------------------------------------------------------

void ComputeShaderManager::bendCurvesOperator(unsigned int curvesSSBO, glm::vec3 direction, float intensity)
{
	GLint SSBOSize = 0;
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, curvesSSBO);
	glGetBufferParameteriv(GL_SHADER_STORAGE_BUFFER, GL_BUFFER_SIZE, &SSBOSize);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	unsigned int curveCount = SSBOSize / (sizeof(glm::vec4) * 5);

	// use shader & send uniforms
	bendCurvesShader.use();
	glUniform1f(glGetUniformLocation(bendCurvesShader.getID(), "u_intensity"), intensity);
	glUniform1ui(glGetUniformLocation(bendCurvesShader.getID(), "u_curveCount"), curveCount);
	glUniform3fv(glGetUniformLocation(bendCurvesShader.getID(), "u_direction"), 1, glm::value_ptr(direction));

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, curvesSSBO);

	glDispatchCompute((int(curveCount) / 128) + 1, 1, 1);
}
