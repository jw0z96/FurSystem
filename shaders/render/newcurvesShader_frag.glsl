#version 330 core

// The output colour. At location 0 it will be sent to the screen.
layout (location = 0) out vec4 fragColor;

uniform mat4 M;
uniform mat4 MV;
uniform mat4 MVP;
uniform mat3 normalMatrix; // This is the inverse transpose of the mv matrix
uniform vec3 camPos;
uniform vec3 colour;

smooth in vec3 WorldPos;

void main()
{
	fragColor = vec4(colour, 1.0);
}
