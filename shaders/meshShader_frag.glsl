#version 330 core

// The output colour. At location 0 it will be sent to the screen.
layout (location = 0) out vec4 fragColor;

uniform mat4 M;
uniform mat4 MV;
uniform mat4 MVP;
uniform mat3 normalMatrix; // This is the inverse transpose of the mv matrix
uniform vec3 camPos;
uniform vec3 u_colour;

smooth in vec3 WorldPos;
smooth in vec3 Normal;
smooth in vec2 TexCoords;

void main()
{
	vec3 view = normalize(camPos - WorldPos);
	float ndotv = max(dot(Normal, view), 0.0);
	fragColor = vec4(u_colour * ndotv, 1.0);
}
