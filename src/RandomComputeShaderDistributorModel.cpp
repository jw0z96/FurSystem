#include "RandomComputeShaderDistributorModel.h"

#include "ComputeShaderManager.h"

RandomComputeShaderDistributorModel::RandomComputeShaderDistributorModel() :
	RandomDistributorModel()
{
	m_MeshSSBOID = 0;
}

RandomComputeShaderDistributorModel::~RandomComputeShaderDistributorModel() {}

void RandomComputeShaderDistributorModel::meshChanged()
{
	std::cout<<"update SSBO for mesh here\n";
	ComputeShaderManager::getInstance()->createMeshSSBO(m_MeshSSBOID, m_mesh);
	RandomDistributorModel::meshChanged();
}

void RandomComputeShaderDistributorModel::distribute()
{
	RandomDistributorModel::distribute();
}
