#include "AbstractDistributorModel.h"

#include <QtCore/QEvent>

#include "MeshData.h"
#include "CurvesData.h"

AbstractDistributorModel::AbstractDistributorModel()
{
	m_curves = Curves();
}

AbstractDistributorModel::~AbstractDistributorModel() {}

unsigned int AbstractDistributorModel::nPorts(PortType portType) const
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

bool AbstractDistributorModel::eventFilter(QObject *object, QEvent *event)
{
	return false;
}

NodeDataType AbstractDistributorModel::dataType(PortType portType, PortIndex portIndex) const
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

std::shared_ptr<NodeData> AbstractDistributorModel::outData(PortIndex)
{
	return std::make_shared<CurvesData>(m_curves);
}

void AbstractDistributorModel::setInData(std::shared_ptr<NodeData> nodeData, PortIndex)
{
	_nodeData = nodeData;

	if (_nodeData) // connected or updated
	{
		m_mesh = std::static_pointer_cast<MeshData>(_nodeData)->mesh();
		distribute();
	}
	else // disconnected
	{
		m_curves.m_curves.clear();
		m_mesh = Mesh();
		emit dataUpdated(0);
	}

}

void AbstractDistributorModel::distribute()
{
}

void AbstractDistributorModel::updateDistribution()
{
	m_curves.m_curves.clear();
	distribute();
	emit dataUpdated(0);
}
