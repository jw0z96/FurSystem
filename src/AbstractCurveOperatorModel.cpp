#include "AbstractCurveOperatorModel.h"

#include <QtCore/QEvent>

#include "MeshData.h"

#include "ComputeShaderManager.h"

AbstractCurveOperatorModel::AbstractCurveOperatorModel()
{
	m_curves = Curves();
	_nodeData = nullptr;
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
	if(_nodeData) // so we dont die if nothing is connected to the input
	{
		switch (std::static_pointer_cast<CurvesData>(_nodeData)->curveType())
		{
			case CPU:
				return std::make_shared<CurvesData>(m_curves);
				break;

			case SSBO:
				return std::make_shared<CurvesData>(m_curvesSSBO);
				break;
		}
	}

	// TODO: what do we do if nothing is connected???
	return std::make_shared<CurvesData>(m_curves);
}

void AbstractCurveOperatorModel::setInData(std::shared_ptr<NodeData> nodeData, PortIndex)
{
	if(nodeData)
		_nodeData = std::static_pointer_cast<CurvesData>(nodeData);

	if (_nodeData) // connected or updated
	{
		updateCurves();
	}
	else // disconnected
	{
		m_curves = Curves();
		// clear ssbo???
		emit dataUpdated(0);
	}
}

void AbstractCurveOperatorModel::operateCurves()
{
}

void AbstractCurveOperatorModel::resetCurves()
{
	switch (_nodeData->curveType())
	{
		case CPU:
			m_curves = _nodeData->curves();
			break;

		case SSBO:
			ComputeShaderManager::getInstance()->copyCurvesSSBO(_nodeData->curvesSSBO(), m_curvesSSBO);
			break;
	}
}

void AbstractCurveOperatorModel::updateCurves()
{
	resetCurves();
	operateCurves();
	emit dataUpdated(0);
}
