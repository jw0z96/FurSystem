#version 430 core

layout(points) in;
layout(triangle_strip, max_vertices = 10) out;

struct Curve
{
	vec4 position[5];
	float length;
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

smooth out float vertIndex;

void main()
{
	uint curveID = gl_PrimitiveIDIn;

	for (int i = 0; i < 5; ++i)
	{
		vertIndex = float(i);
		vec3 pos = curves[curveID].position[i].xyz;
		// gl_Position = MVP * vec4(pos, 1.0);
		// EmitVertex();
		float widthFactor = 1.0 - (i / 4.0);

		vec3 nextPos;
		if (i == 4)
		{
			nextPos = curves[curveID].position[i - 1].xyz;
		}
		else
		{
			nextPos = curves[curveID].position[i + 1].xyz;
		}
		vec3 widthVec = cross((camPos - pos), (nextPos - pos));
		widthVec = normalize(widthVec) * 0.005 * widthFactor;
		gl_Position = MVP * vec4((pos + widthVec), 1.0);
		EmitVertex();
		gl_Position = MVP * vec4((pos - widthVec), 1.0);
		EmitVertex();
	}
	EndPrimitive();
}
