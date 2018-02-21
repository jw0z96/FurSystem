#include "RandomComputeShaderDistributorModel.h"

#include "CurvesData.h"

#include "ComputeShaderManager.h"

RandomComputeShaderDistributorModel::RandomComputeShaderDistributorModel() :
	RandomDistributorModel()
{
	m_meshSSBOID = 0;
	m_curvesSSBOID = 0;
}

RandomComputeShaderDistributorModel::~RandomComputeShaderDistributorModel()
{
	glDeleteBuffers(1, &m_meshSSBOID);
	glDeleteBuffers(1, &m_curvesSSBOID);
}

void RandomComputeShaderDistributorModel::meshChanged()
{
	std::cout<<"update SSBO for mesh here\n";
	ComputeShaderManager::getInstance()->createMeshSSBO(m_meshSSBOID, m_mesh);
	RandomDistributorModel::meshChanged(); // recalculate the mesh area
}

void RandomComputeShaderDistributorModel::distribute()
{
	// this function needs to create / resize m_curvesSSBOID
	ComputeShaderManager::getInstance()->randomDistribution(
		m_meshSSBOID,
		m_curvesSSBOID,
		m_spinbox->value(),
		m_mesh.m_faces.size(),
		m_totalMeshArea
		);
}

std::shared_ptr<NodeData> RandomComputeShaderDistributorModel::outData(PortIndex)
{
	return std::make_shared<CurvesData>(m_curvesSSBOID);
}
