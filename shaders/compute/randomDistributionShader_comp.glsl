#version 430

layout (local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

// TOO LAZY TO PAD MANUALLY, REMEMBER TO ONLY ACCESS .XYZ
struct Face
{
	vec4 position[3];
	vec4 normal[3];
	vec4 uv[3];
	float area;
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

float rand(vec2 co)
{
	return fract(sin(dot(co.xy,vec2(12.9898,78.233))) * 43758.5453);
}

// ----------------------------------------------------------------------------

void main()
{
	uint computeIndex = gl_GlobalInvocationID.x;

	if (computeIndex > u_curveCount)
		return;

	// float indexWeight = rand(vec2(computeIndex, 0.0));
	float indexWeight = float(computeIndex) / float(u_curveCount);
	// float areaWeighting = 1.0 / u_meshArea;
	float weight = 0.0;

	for (int i = 0; i < u_faceCount; ++i)
	{
		weight += (faces[i].area / u_meshArea);

		if (weight > indexWeight)
		{
			float baryA = rand(vec2(computeIndex, 20.0));
			float baryB = rand(vec2(computeIndex, 10.0));

			if ((baryA + baryB) > 1.0)
			{
				baryA = 1.0 - baryA;
				baryB = 1.0 - baryB;
			}

			float baryC = 1.0 - baryA - baryB;

			vec3 posA = faces[i].position[0].xyz;
			vec3 posB = faces[i].position[1].xyz;
			vec3 posC = faces[i].position[2].xyz;

			vec3 normA = faces[i].normal[0].xyz;
			vec3 normB = faces[i].normal[1].xyz;
			vec3 normC = faces[i].normal[2].xyz;

			vec3 randPos = posA * baryA + posB * baryB + posC * baryC;
			vec3 randNorm = normalize(normA * baryA + normB * baryB + normC * baryC);

			for (int j = 0; j < 5; ++j)
			{
				curves[computeIndex].position[j] = vec4((randPos + (float(j) * randNorm * 0.01f)), 0.0);
			}

			return;
		}
	}
}
