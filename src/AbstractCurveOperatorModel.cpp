#include "AbstractCurveOperatorModel.h"

#include <QtCore/QEvent>

#include "MeshData.h"
#include "CurvesData.h"

AbstractCurveOperatorModel::AbstractCurveOperatorModel()
{
	m_curves = Curves();
}

AbstractCurveOperatorModel::~AbstractCurveOperatorModel() {}

unsigned int AbstractCurveOperatorModel::nPorts(PortType portType) const
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

bool AbstractCurveOperatorModel::eventFilter(QObject *object, QEvent *event)
{
	return false;
}

NodeDataType AbstractCurveOperatorModel::dataType(PortType portType, PortIndex portIndex) const
{
	switch (portType)
	{
		case PortType::In:
			switch (portIndex)
			{
				case 0:
					return CurvesData().type();
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

std::shared_ptr<NodeData> AbstractCurveOperatorModel::outData(PortIndex)
{
	return std::make_shared<CurvesData>(m_curves);
}

void AbstractCurveOperatorModel::setInData(std::shared_ptr<NodeData> nodeData, PortIndex)
{
	_nodeData = nodeData;

	if (_nodeData) // connected or updated
	{
		// resetCurves();
		operateCurves();
	}
	else // disconnected
	{
		m_curves = Curves();
	}

	emit dataUpdated(0);
}

void AbstractCurveOperatorModel::operateCurves()
{
}

void AbstractCurveOperatorModel::resetCurves()
{
	m_curves = std::static_pointer_cast<CurvesData>(_nodeData)->curves();
}
