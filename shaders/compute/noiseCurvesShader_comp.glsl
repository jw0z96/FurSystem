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

// ----------------------------------------------------------------------------

float rand(vec2 co)
{
	return fract(sin(dot(co.xy,vec2(12.9898,78.233))) * 43758.5453);
}

// ----------------------------------------------------------------------------

void main()
{
	uint computeIndex = gl_GlobalInvocationID.x;

	if (computeIndex >= u_curveCount)
		return;

	Curve newCurve = curves[computeIndex];

	vec3 diffs[4];
	for (int i = 0; i < 4; ++i)
	{
		diffs[i] = newCurve.position[i + 1].xyz - newCurve.position[i].xyz;

		vec3 randVec = vec3(
			rand(vec2(i, computeIndex)),
			rand(vec2(i, computeIndex + 1)),
			rand(vec2(i, computeIndex + 2))
			);
		randVec *= 2.0;
		randVec -= vec3(1.0);

		diffs[i] = mix(diffs[i], randVec, u_intensity * 0.1);
		diffs[i] = 0.25 * newCurve.length * normalize(diffs[i]);
	}

	for (int i = 1; i < 5; ++i)
	{
		newCurve.position[i].xyz = newCurve.position[i - 1].xyz + diffs[i - 1];
	}

	curves[computeIndex] = newCurve;
}
