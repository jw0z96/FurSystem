#include "ComputeManager.h"

//----------------------------------------------------------------------------------------------------------------------

ComputeManager* ComputeManager::m_instance = NULL;

//----------------------------------------------------------------------------------------------------------------------

ComputeManager::ComputeManager()
{
}

//----------------------------------------------------------------------------------------------------------------------

ComputeManager::~ComputeManager()
{
	std::cout<<"~ComputeManager\n";
}

//----------------------------------------------------------------------------------------------------------------------

void ComputeManager::cleanUpAll()
{
}
