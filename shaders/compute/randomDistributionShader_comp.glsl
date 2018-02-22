#version 430

layout (local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

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

	float indexWeight = rand(vec2(computeIndex, 0.0));
	float areaWeighting = 1.0 / u_meshArea;
	float weight = 0.0;

	for (uint i = 0; i < u_faceCount; ++i)
	{
		vec3 posA = faces[i].position[0].xyz;
		vec3 posB = faces[i].position[1].xyz;
		vec3 posC = faces[i].position[2].xyz;

		vec3 e1 = posB - posA;
		vec3 e2 = posC - posA;
		vec3 e3 = cross(e1, e2);

		float triArea = 0.5 * sqrt(e3.x * e3.x + e3.y * e3.y + e3.z * e3.z);
		weight += (triArea * areaWeighting);

		if (weight > indexWeight)
		{
			float baryA = rand(vec2(5.0, 5.0 * float(i)));
			float baryB = rand(vec2(7.0 * float(i), 7.0));

			if ((baryA + baryB) > 1.0)
			{
				baryA = 1.0 - baryA;
				baryB = 1.0 - baryB;
			}

			float baryC = 1.0 - baryA - baryB;

			vec3 normA = faces[i].normal[0].xyz;
			vec3 normB = faces[i].normal[1].xyz;
			vec3 normC = faces[i].normal[2].xyz;

			vec3 randPos = posA * baryA + posB * baryB + posC * baryC;
			vec3 randNorm = normalize(normA * baryA + normB * baryB + normC * baryC);

			for (int j = 0; j < 5; ++j)
			{
				curves[computeIndex].position[j] = vec4((randPos + (float(j) * randNorm * 0.01f)), 0.0);
			}

			break;
		}
	}
}
