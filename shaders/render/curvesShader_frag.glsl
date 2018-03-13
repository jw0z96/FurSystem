#version 430 core

// The output colour. At location 0 it will be sent to the screen.
layout (location = 0) out vec4 fragColor;

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
uniform vec3 u_colour;
uniform uint u_numIndices;
uniform float u_roughness;
uniform float u_metallic;

smooth in vec3 WorldPos;
smooth in float vertIndex;
flat in uint curveID;

const float PI = 3.14159265359;
const float HALF_PI = 1.57079f;

// ----------------------------------------------------------------------------
/// PBR FUNCTIONS
// ----------------------------------------------------------------------------

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
	float a = roughness*roughness;
	float a2 = a*a;
	float NdotH = max(dot(N, H), 0.0);
	float NdotH2 = NdotH*NdotH;

	float nom   = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return nom / denom;
}

// ----------------------------------------------------------------------------

float GeometrySchlickGGX(float NdotV, float roughness)
{
	float r = (roughness + 1.0);
	float k = (r*r) / 8.0;

	float nom   = NdotV;
	float denom = NdotV * (1.0 - k) + k;

	return nom / denom;
}

// ----------------------------------------------------------------------------

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
	float NdotV = max(dot(N, V), 0.0);
	float NdotL = max(dot(N, L), 0.0);
	float ggx2 = GeometrySchlickGGX(NdotV, roughness);
	float ggx1 = GeometrySchlickGGX(NdotL, roughness);

	return ggx1 * ggx2;
}

// ----------------------------------------------------------------------------

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

// ----------------------------------------------------------------------------

// https://knarkowicz.wordpress.com/2016/01/06/aces-filmic-tone-mapping-curve/
vec3 acesFilm(const vec3 x) {
	const float a = 2.51;
	const float b = 0.03;
	const float c = 2.43;
	const float d = 0.59;
	const float e = 0.14;
	return clamp((x * (a * x + b)) / (x * (c * x + d ) + e), 0.0, 1.0);
}

// ----------------------------------------------------------------------------

void main()
{
	float a = float(vertIndex) / 4.0;
	// fragColor = vec4(u_colour * a, 1.0);
	int index = int(floor(vertIndex));
	// vec3 posA = curves[curveID].position[index - 1].xyz;
	vec3 posA = curves[curveID].position[index].xyz;
	vec3 posB = curves[curveID].position[index + 1].xyz;

	vec3 normal = normalize(posB - posA);
	vec3 position = mix(posA, posB, fract(a));

	vec3 viewDirection = normalize(camPos - position);
	vec3 lightDirection = normalize(vec3(1.0, 1.0, 0.0)); // vec4(1.0) is the light direction
	vec3 lightVector = normalize((vec4(lightDirection, 1.0) * MVP).xyz); // vec4(1.0) is the light direction
	vec3 halfVector = normalize(viewDirection + lightVector);

	float metallic = u_metallic;
	float roughness = u_roughness;
	vec3 albedo = u_colour * a;
	vec3 F0 = vec3(0.01);
	F0 = mix(F0, albedo, metallic);

	// Cook-Torrance BRDF
	float NDF = DistributionGGX(normal, halfVector, roughness);
	float G = GeometrySmith(normal, viewDirection, lightVector, roughness);
	vec3 F = fresnelSchlick(max(dot(halfVector, viewDirection), 0.0), F0);
	vec3 nominator = NDF * G * F;
	float denominator = 4 * max(dot(normal, viewDirection), 0.0) * max(dot(normal, lightVector), 0.0) + 0.001; // 0.001 to prevent divide by zero.
	vec3 specular = nominator / denominator;
	// kS is equal to Fresnel
	vec3 kS = F;
	vec3 kD = vec3(1.0) - kS;
	kD *= 1.0 - metallic;

	vec3 Lo = (kD * albedo / PI + specular) * 4.0; // * a

	fragColor = vec4(acesFilm(Lo), 1.0);
}
