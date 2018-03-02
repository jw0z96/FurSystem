#version 430

layout (local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

struct Curve
{
	vec4 position[5];
};

layout (std430, binding = 0) buffer curvesBuffer
{
	Curve curves[];
};

layout (std430, binding = 1) buffer clumpCurvesBuffer
{
	Curve clumpCurves[];
};

uniform uint u_curveCount;
uniform uint u_clumpCurveCount;
uniform uint u_mode;

// ----------------------------------------------------------------------------

uint findClosestCurve(uint computeIndex)
{
	vec3 clumpPos = clumpCurves[computeIndex].position[0].xyz;
	uint closest = 0;
	float curveDistance = distance(clumpPos, curves[closest].position[0].xyz);

	for (uint i = 1; i < u_curveCount; ++i)
	{
		float testDistance = distance(clumpPos, curves[i].position[0].xyz);
		if (testDistance < curveDistance)
		{
			curveDistance = testDistance;
			closest = i;
		}
	}

	return closest;
}

// ----------------------------------------------------------------------------

uint findClosestClumpCurve(uint computeIndex)
{
	vec3 curvePos = curves[computeIndex].position[0].xyz;
	uint closest = 0;
	float curveDistance = distance(curvePos, clumpCurves[closest].position[0].xyz);

	for (uint i = 1; i < u_clumpCurveCount; ++i)
	{
		float testDistance = distance(curvePos, clumpCurves[i].position[0].xyz);
		if (testDistance < curveDistance)
		{
			curveDistance = testDistance;
			closest = i;
		}
	}

	return closest;
}

// ----------------------------------------------------------------------------

void main()
{
	uint computeIndex = gl_GlobalInvocationID.x;

	if (u_mode == 0) // finding closest curves
	{
		if (computeIndex >= u_clumpCurveCount)
			return;

		uint closestCurveIndex = findClosestCurve(computeIndex);
		clumpCurves[computeIndex] = curves[closestCurveIndex];
	}
	else if (u_mode == 1) // actually clump the curves
	{
		if (computeIndex >= u_curveCount)
			return;

		uint closestClumpCurveIndex = findClosestClumpCurve(computeIndex);

		for (int i = 0; i < 5; ++i)
		{
			float factor = float(i) / 4.0;
			vec3 curvePos = curves[computeIndex].position[i].xyz;
			vec3 clumpPos = clumpCurves[closestClumpCurveIndex].position[i].xyz;
			vec3 pos = mix(curvePos, clumpPos, factor);
			curves[computeIndex].position[i] = vec4(pos, 0.0);
		}
	}
}
