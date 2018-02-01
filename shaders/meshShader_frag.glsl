#version 430

// The output colour. At location 0 it will be sent to the screen.
layout (location = 0) out vec4 fragColor;

uniform mat4 M;
uniform mat4 MV;
uniform mat4 MVP;
uniform mat3 normalMatrix; // This is the inverse transpose of the mv matrix
uniform vec3 camPos;

in vec3 WorldPos;
in vec3 Normal;
in vec2 TexCoords;

void main()
{
	fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
