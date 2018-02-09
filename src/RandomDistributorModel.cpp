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
}

RandomDistributorModel::~RandomDistributorModel() {}

void RandomDistributorModel::distribute()
{
	m_curves.m_curves.clear();

	float maxDensity = 5.0;

	// unsigned int seed = 1470;

	std::random_device rd; //Will be used to obtain a seed for the random number engine
	std::mt19937 generator(rd()); // mt19937 is a standard mersenne_twister_engine
	std::uniform_real_distribution<float> distribution(0.0, 1.0);

	for (unsigned int i = 0; i < m_spinbox->value(); ++i)
	{
		unsigned int index = floor(generator() % m_mesh.m_faces.size());

		auto face = m_mesh.m_faces[index];

		glm::vec3 posA = m_mesh.m_vertexPositions[face.pos[0]];
		glm::vec3 posB = m_mesh.m_vertexPositions[face.pos[1]];
		glm::vec3 posC = m_mesh.m_vertexPositions[face.pos[2]];

		glm::vec3 normA = m_mesh.m_vertexNormals[face.normal[0]];
		glm::vec3 normB = m_mesh.m_vertexNormals[face.normal[1]];
		glm::vec3 normC = m_mesh.m_vertexNormals[face.normal[2]];

		float baryA = distribution(generator);
		float baryB = distribution(generator);

		if ((baryA + baryB) > 1.0)
		{
			baryA = 1.0 - baryA;
			baryB = 1.0 - baryB;
		}

		float baryC = 1.0 - baryA - baryB;

		glm::vec3 randPos = posA * baryA + posB * baryB + posC * baryC;
		glm::vec3 randNorm = glm::normalize(normA * baryA + normB * baryB + normC * baryC);

		Curve curve;
		for (int j = 0; j < 5; ++j)
		{
			curve.vertices[j] = randPos + (float(j) * randNorm * 0.01f);
		}
		m_curves.m_curves.push_back(curve);
	}
}
