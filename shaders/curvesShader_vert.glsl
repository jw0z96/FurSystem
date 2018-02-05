#version 430 core

uniform mat4 M;
uniform mat4 MV;
uniform mat4 MVP;
uniform mat3 normalMatrix; // This is the inverse transpose of the mv matrix
uniform vec3 camPos;

layout (location = 0) in vec3 inPos;

smooth out vec3 WorldPos;

void main()
{
	// pass worldspace position to fragment shader
	WorldPos = vec3(M * vec4(inPos, 1.0));
	// transform input vertex
	gl_Position = MVP * vec4(inPos, 1.0);
}
