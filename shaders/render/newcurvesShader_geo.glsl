#version 430 core

layout(points) in;
layout(line_strip, max_vertices = 5) out;

struct Curve
{
	vec4 position[5];
};

layout (std430, binding = 0) buffer curvesBuffer
{
	Curve curves[];
};

uniform mat4 M;
uniform mat4 MV;
uniform mat4 MVP;
uniform mat3 normalMatrix; // This is the inverse transpose of the mv matrix
uniform vec3 camPos;
uniform vec3 colour;

void main()
{
	int curveID = gl_PrimitiveIDIn;

	for (int i = 0; i < 5; ++i)
	{
		gl_Position = MVP * curves[curveID].position[i];
		EmitVertex();
	}

	EndPrimitive();
}
