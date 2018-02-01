#include "MeshRendererModel.h"

#include <QtCore/QEvent>
#include <QtCore/QDir>

#include <QtWidgets/QFileDialog>

#include "MeshData.h"
#include "RenderableManager.h"

MeshRendererModel::MeshRendererModel()
{
	m_meshRenderable = std::make_shared<MeshRenderable>();
}

unsigned int MeshRendererModel::nPorts(PortType portType) const
{
	unsigned int result = 1;

	switch (portType)
	{
		case PortType::In:
			result = 1;
			break;

		case PortType::Out:
			result = 0;

		default:
			break;
	}

	return result;
}

bool MeshRendererModel::eventFilter(QObject *object, QEvent *event)
{
	return false;
}

NodeDataType MeshRendererModel::dataType(PortType, PortIndex) const
{
	return MeshData().type();
}


std::shared_ptr<NodeData> MeshRendererModel::outData(PortIndex)
{
	return _nodeData;
}

void MeshRendererModel::setInData(std::shared_ptr<NodeData> nodeData, PortIndex)
{
	_nodeData = nodeData;

	if (_nodeData) // connected
	{
		// deregister the current renderable from the viewport
		RenderableManager::getInstance()->deregisterRenderable(m_meshRenderable);
		auto d = std::static_pointer_cast<MeshData>(_nodeData);
		m_meshRenderable = std::make_shared<MeshRenderable>(d->mesh());
		std::cout<<"register the renderable with the viewport\n";
		RenderableManager::getInstance()->registerRenderable(m_meshRenderable);
	}
	else // disconnected
	{
		std::cout<<"deregister the renderable from the viewport\n";
		RenderableManager::getInstance()->deregisterRenderable(m_meshRenderable);
	}
}
