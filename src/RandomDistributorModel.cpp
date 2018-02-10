#include "RandomDistributorModel.h"

#include <random>

RandomDistributorModel::RandomDistributorModel() :
	m_spinbox(new QSpinBox())
{
	m_spinbox->setRange(0, 100000);
	m_spinbox->setSingleStep(100);
	m_spinbox->setValue(1000);

	connect(m_spinbox, SIGNAL(valueChanged(int)), this, SLOT(updateDistribution()));

	m_curves = Curves();

	m_totalMeshArea = 0.0;
}

RandomDistributorModel::~RandomDistributorModel() {}

void RandomDistributorModel::meshChanged()
{
	m_totalMeshArea = calculateMeshArea();
}

void RandomDistributorModel::distribute()
{
	m_curves.m_curves.clear();

	std::random_device rd; //Will be used to obtain a seed for the random number engine
	std::mt19937 generator(rd()); // mt19937 is a standard mersenne_twister_engine
	std::uniform_real_distribution<float> distribution(0.0, 1.0);

	float areaWeighting = 1.0 / m_totalMeshArea;

	for (unsigned int i = 0; i < m_spinbox->value(); ++i)
	{
		float indexWeight = distribution(generator);
		float weight = 0.0;

		for (auto face : m_mesh.m_faces)
		{
			glm::vec3 posA = m_mesh.m_vertexPositions[face.pos[0]];
			glm::vec3 posB = m_mesh.m_vertexPositions[face.pos[1]];
			glm::vec3 posC = m_mesh.m_vertexPositions[face.pos[2]];

			glm::vec3 e1 = posB - posA;
			glm::vec3 e2 = posC - posA;
			glm::vec3 e3 = glm::cross(e1, e2);

			float triArea = 0.5 * sqrt(e3.x * e3.x + e3.y * e3.y + e3.z * e3.z);
			weight += (triArea * areaWeighting);

			if (weight > indexWeight)
			{
				float baryA = distribution(generator);
				float baryB = distribution(generator);

				if ((baryA + baryB) > 1.0)
				{
					baryA = 1.0 - baryA;
					baryB = 1.0 - baryB;
				}

				float baryC = 1.0 - baryA - baryB;

				glm::vec3 normA = m_mesh.m_vertexNormals[face.normal[0]];
				glm::vec3 normB = m_mesh.m_vertexNormals[face.normal[1]];
				glm::vec3 normC = m_mesh.m_vertexNormals[face.normal[2]];

				glm::vec3 randPos = posA * baryA + posB * baryB + posC * baryC;
				glm::vec3 randNorm = glm::normalize(normA * baryA + normB * baryB + normC * baryC);

				Curve curve;

				for (int j = 0; j < 5; ++j)
				{
					curve.vertices[j] = randPos + (float(j) * randNorm * 0.01f);
				}

				m_curves.m_curves.push_back(curve);

				break;
			}
		}
	}
}

float RandomDistributorModel::calculateMeshArea() const
{
	float totalArea = 0.0;
	for (auto face : m_mesh.m_faces)
	{
		glm::vec3 posA = m_mesh.m_vertexPositions[face.pos[0]];
		glm::vec3 posB = m_mesh.m_vertexPositions[face.pos[1]];
		glm::vec3 posC = m_mesh.m_vertexPositions[face.pos[2]];
		glm::vec3 e1 = posB - posA;
		glm::vec3 e2 = posC - posA;
		glm::vec3 e3 = glm::cross(e1, e2);
		float triArea = 0.5 * sqrt(e3.x * e3.x + e3.y * e3.y + e3.z * e3.z);
		totalArea += triArea;
	}
	return totalArea;
}
