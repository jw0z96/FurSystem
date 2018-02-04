#include "DistributorModel.h"

#include <QtCore/QEvent>

#include "MeshData.h"
#include "CurvesData.h"

DistributorModel::DistributorModel()
{
	m_curves = std::make_shared<Curves>();
}

DistributorModel::~DistributorModel() {}

unsigned int DistributorModel::nPorts(PortType portType) const
{
	unsigned int result = 1;

	switch (portType)
	{
		case PortType::In:
			result = 1;
			break;

		case PortType::Out:
			result = 1;

		default:
			break;
	}

	return result;
}

bool DistributorModel::eventFilter(QObject *object, QEvent *event)
{
	return false;
}

NodeDataType DistributorModel::dataType(PortType portType, PortIndex portIndex) const
{
	switch (portType)
	{
		case PortType::In:
			switch (portIndex)
			{
				case 0:
					return MeshData().type();
			}
			break;

		case PortType::Out:
			switch (portIndex)
			{
				case 0:
					return CurvesData().type();
			}
			break;

		case PortType::None:
			break;
	}
	// FIXME: control may reach end of non-void function [-Wreturn-type]
	return NodeDataType();
}

std::shared_ptr<NodeData> DistributorModel::outData(PortIndex)
{
	return _nodeData;
}

void DistributorModel::setInData(std::shared_ptr<NodeData> nodeData, PortIndex)
{
	_nodeData = nodeData;

	if (_nodeData) // connected or updated
	{
		// register the renderable with the RenderableManager if it isn't already
		// RenderableManager::getInstance()->registerRenderable(m_meshRenderable);
		// auto d = std::static_pointer_cast<MeshData>(_nodeData);
		// m_meshRenderable->setMesh(d->mesh());
		// m_meshRenderable->setVisibility(true);
		// RenderableManager::getInstance()->updateViewport();
	}
	else // disconnected
	{
		// m_meshRenderable->setVisibility(false);
		// RenderableManager::getInstance()->updateViewport();
	}
}
