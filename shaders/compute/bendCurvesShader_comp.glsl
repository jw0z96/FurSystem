#version 430

layout (local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

struct Curve
{
	vec4 position[5];
	float length;
};

layout (std430, binding = 0) buffer curvesBuffer
{
	Curve curves[];
};

uniform float u_intensity;
uniform uint u_curveCount;
uniform vec3 u_direction;

// ----------------------------------------------------------------------------

void main()
{
	uint computeIndex = gl_GlobalInvocationID.x;

	if (computeIndex >= u_curveCount)
		return;

	for (int i = 0; i < 5; ++i)
	{
		vec3 pos = curves[computeIndex].position[i].xyz;
		pos += float(i) * float(i) * u_intensity * u_direction;
		curves[computeIndex].position[i] = vec4(pos, 0.0);
	}
}
