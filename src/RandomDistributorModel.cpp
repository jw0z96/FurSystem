#include "RandomDistributorModel.h"

#include "ComputeShaderManager.h"

#include "CurvesData.h"

#include <random>
// #include <chrono>

RandomDistributorModel::RandomDistributorModel() :
	m_embedded(new QWidget()),
	m_ui(new Ui::RandomDistributorModelWidget())
{
	// setup ui
	m_ui->setupUi(m_embedded);
	// connect spinbox and checkbox
	connect(m_ui->countSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateDistribution()));
	connect(m_ui->modeCheckBox, SIGNAL(stateChanged(int)), this, SLOT(updateDistribution()));
	connect(m_ui->lengthSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateDistribution()));
	connect(m_ui->variationSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateDistribution()));

	m_curves = Curves();
	m_meshSSBOID = 0;
	m_curvesSSBOID = 0;
	m_totalMeshArea = 0.0;
}

RandomDistributorModel::~RandomDistributorModel()
{
	if (m_meshSSBOID)
		glDeleteBuffers(1, &m_meshSSBOID);
	if (m_curvesSSBOID)
		glDeleteBuffers(1, &m_curvesSSBOID);

	delete m_ui;
	// delete m_embedded; // for some reason these cause crash
	// m_embedded->deleteLater();
}

void RandomDistributorModel::meshChanged()
{
	ComputeShaderManager::getInstance()->createMeshSSBO(m_meshSSBOID, m_mesh);
	m_totalMeshArea = calculateMeshArea();
}

void RandomDistributorModel::distribute()
{
// 	auto startDistributionTimer = std::chrono::system_clock::now();
// 	auto endDistributionTimer = startDistributionTimer;

	if (m_ui->modeCheckBox->isChecked()) // GPU mode checked
	{
		// this function needs to create & resize m_curvesSSBOID
		ComputeShaderManager::getInstance()->randomDistribution(
			m_meshSSBOID,
			m_curvesSSBOID,
			m_ui->countSpinBox->value(),
			m_mesh.m_faces.size(),
			m_totalMeshArea,
			m_ui->lengthSpinBox->value(),
			m_ui->variationSpinBox->value()
			);

		// endDistributionTimer = std::chrono::system_clock::now();
	}
	else
	{
		m_curves.m_curves.clear();

		std::random_device rd; //Will be used to obtain a seed for the random number engine
		std::mt19937 generator(rd()); // mt19937 is a standard mersenne_twister_engine
		std::uniform_real_distribution<float> distribution(0.0, 1.0);

		float areaWeighting = 1.0 / m_totalMeshArea;

		for (unsigned int i = 0; i < m_ui->countSpinBox->value(); ++i)
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
					float randLength = m_ui->lengthSpinBox->value() * glm::mix((1.0 - m_ui->variationSpinBox->value()), 1.0, distribution(generator));

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
						curve.vertices[j] = randPos + ((float(j) / 5.0f) * randNorm * randLength);
					}
					curve.length = randLength;

					m_curves.m_curves.push_back(curve);
					break;
				}
			}
		}

		// endDistributionTimer = std::chrono::system_clock::now();
	}

	// auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endDistributionTimer - startDistributionTimer);
	// std::cout << "distribution of "<<m_ui->countSpinBox->value()<<" took: " << elapsed.count() << "ms\n";
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

std::shared_ptr<NodeData> RandomDistributorModel::outData(PortIndex)
{
	if (m_ui->modeCheckBox->isChecked()) // GPU mode checked
	{
		return std::make_shared<CurvesData>(m_curvesSSBOID);
	}
	else
	{
		return std::make_shared<CurvesData>(m_curves);
	}
}
