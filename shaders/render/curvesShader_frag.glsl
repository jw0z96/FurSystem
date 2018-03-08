#version 330 core

// The output colour. At location 0 it will be sent to the screen.
layout (location = 0) out vec4 fragColor;

uniform mat4 M;
uniform mat4 MV;
uniform mat4 MVP;
uniform mat3 normalMatrix; // This is the inverse transpose of the mv matrix
uniform vec3 camPos;
uniform vec3 u_colour;
uniform uint u_numIndices;

smooth in vec3 WorldPos;

smooth in float vertIndex;

void main()
{
	float a = float(vertIndex) / 5.0;
	fragColor = vec4(u_colour * a, 1.0);
	// fragColor = vec4(u_colour, 1.0);
}
