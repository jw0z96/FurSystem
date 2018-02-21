#version 430

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

// TOO LAZY TO PAD MANUALLY, REMEMBER TO ONLY ACCESS .XYZ
struct Face
{
	vec4 position[3];
	vec4 normal[3];
	vec4 uv[3];
};

struct Curve
{
	vec4 position[5];
};

layout (std430, binding = 0) buffer facesBuffer
{
	Face faces[];
};

layout (std430, binding = 1) buffer curvesBuffer
{
	Curve curves[];
};

uniform float u_meshArea;
uniform uint u_curveCount;
uniform uint u_faceCount;

// ----------------------------------------------------------------------------

void main()
{
	uint computeIndex = gl_GlobalInvocationID.x;
}
