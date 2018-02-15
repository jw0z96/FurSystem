#include "ComputeShaderManager.h"

#include <iostream>

//----------------------------------------------------------------------------------------------------------------------

ComputeShaderManager* ComputeShaderManager::m_instance = NULL;

//----------------------------------------------------------------------------------------------------------------------

ComputeShaderManager::ComputeShaderManager()
{
}

//----------------------------------------------------------------------------------------------------------------------

ComputeShaderManager::~ComputeShaderManager()
{
	std::cout<<"~ComputeShaderManager\n";
}

//----------------------------------------------------------------------------------------------------------------------

void ComputeShaderManager::cleanUpAll()
{
}

//----------------------------------------------------------------------------------------------------------------------

void ComputeShaderManager::registerMesh()
{
	std::cout<<"creating an SSBO\n";
}
