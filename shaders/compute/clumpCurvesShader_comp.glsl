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

layout (std430, binding = 1) buffer clumpCurvesBuffer
{
	Curve clumpCurves[];
};

uniform uint u_curveCount;
uniform uint u_clumpCurveCount;
uniform uint u_mode;
uniform float u_envelope;
uniform bool u_preserveLength;

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

Curve resampleCurve(Curve curve)
{
	float originalLength = curve.length;

	// float lengths[4];
	// vec3 diffs[4];
	// for (int i = 0; i < 4; ++i)
	// {
	// 	diffs[i] = curve.position[i + 1].xyz - curve.position[i].xyz;
	// 	lengths[i] = length(diffs[i]);
	// }

	Curve newCurve;
	newCurve.position[0] = curve.position[0];
	for (int i = 1; i < 5; ++i)
	{
		// float targetLength = (i * originalLength) / 4.0;
		// float accumLength = 0.0;
		// for (int j = 0; j < 4; ++j)
		// {
		// 	accumLength += lengths[j];
		// 	if (accumLength >= targetLength)
		// 	{
		// 		float factor = (accumLength - targetLength) / lengths[j];
		// 		vec3 newPos = mix(curve.position[j].xyz, curve.position[j + 1].xyz, (1.0 - factor));
		// 		vec3 newDiff = (originalLength / 4.0) * normalize(newPos- newCurve.position[i - 1].xyz);
		// 		// newCurve.position[i] = mix(curve.position[j], curve.position[j + 1], (1.0 - factor));
		// 		newCurve.position[i] = vec4(newCurve.position[i - 1].xyz + newDiff, 1.0);
		// 		break;
		// 	}
		// }
		vec3 newDiff = 0.25 * originalLength * normalize(curve.position[i].xyz - newCurve.position[i - 1].xyz);
		// vec3 newDiff = 0.2 * originalLength * normalize(curve.position[i].xyz - newCurve.position[i - 1].xyz); // why is it 0.2??
		newCurve.position[i].xyz = newCurve.position[i - 1].xyz + newDiff;
	}
	newCurve.length = originalLength;

	return newCurve;
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
		float originalLength = curves[computeIndex].length;

		Curve newCurve = curves[computeIndex];

		for (int i = 0; i < 5; ++i)
		{
			float factor = float(i) / 4.0;
			vec3 curvePos = newCurve.position[i].xyz;
			vec3 clumpPos = clumpCurves[closestClumpCurveIndex].position[i].xyz;
			vec3 pos = mix(curvePos, clumpPos, factor * u_envelope);
			newCurve.position[i] = vec4(pos, 0.0);
		}

		if (u_preserveLength)
			newCurve = resampleCurve(newCurve);

		curves[computeIndex] = newCurve;
	}
}
