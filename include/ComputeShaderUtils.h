#ifndef COMPUTESHADERUTILS_H
#define COMPUTESHADERUTILS_H

struct SSBO_Face
{
	glm::vec4 position[3];
	glm::vec4 normal[3];
	glm::vec4 uv[3];
	float area; float pad[3];
};

unsigned int getIndicesFromCurveSSBO(unsigned int _ssbo)
{
	GLint SSBOSize = 0;
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
	glGetBufferParameteriv(GL_SHADER_STORAGE_BUFFER, GL_BUFFER_SIZE, &SSBOSize);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	return (SSBOSize / (sizeof(glm::vec4) * 6));
}

#endif // COMPUTESHADERUTILS_H
