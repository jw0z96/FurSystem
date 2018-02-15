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
	ComputeShaderManager::getInstance()->registerMesh();
	RandomDistributorModel::meshChanged();
}

void RandomComputeShaderDistributorModel::distribute()
{
	RandomDistributorModel::distribute();
}
