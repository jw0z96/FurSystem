#include "BasicDistributorModel.h"

BasicDistributorModel::BasicDistributorModel()
{
	m_curves = Curves();
}

BasicDistributorModel::~BasicDistributorModel() {}

void BasicDistributorModel::distribute()
{
	m_curves.m_curves.clear();

	for (auto face : m_mesh.m_faces)
	{
		glm::vec3 posA = m_mesh.m_vertexPositions[face.pos[0]];
		glm::vec3 posB = m_mesh.m_vertexPositions[face.pos[1]];
		glm::vec3 posC = m_mesh.m_vertexPositions[face.pos[2]];

		glm::vec3 e1 = posB - posA;
		glm::vec3 e2 = posC - posA;
		glm::vec3 e3 = glm::cross(e1, e2);

		float triArea = 0.5 * sqrt(e3.x * e3.x + e3.y * e3.y + e3.z * e3.z);

		glm::vec3 basePos = posA;
		basePos += posB;
		basePos += posC;
		basePos /= 3.0;

		glm::vec3 baseNorm = m_mesh.m_vertexNormals[face.normal[0]];
		baseNorm += m_mesh.m_vertexNormals[face.normal[1]];
		baseNorm += m_mesh.m_vertexNormals[face.normal[2]];
		baseNorm = glm::normalize(baseNorm);

		Curve curve;
		for (int j = 0; j < 5; ++j)
		{
			curve.vertices[j] = basePos + (float(j) * baseNorm * 0.1f);
		}
		m_curves.m_curves.push_back(curve);
	}

}
