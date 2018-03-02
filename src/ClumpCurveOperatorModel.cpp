#include "ClumpCurveOperatorModel.h"

#include "ComputeShaderManager.h"

#include "CurvesData.h"

ClumpCurveOperatorModel::ClumpCurveOperatorModel() :
	AbstractCurveOperatorModel()
{
	m_clumpCurves = Curves();
	m_clumpCurvesSSBO = 0;
	m_clumpNodeData = nullptr;
}

ClumpCurveOperatorModel::~ClumpCurveOperatorModel()
{
	if (m_clumpCurvesSSBO)
		glDeleteBuffers(1, &m_clumpCurvesSSBO);
}

QString ClumpCurveOperatorModel::portCaption(PortType portType, PortIndex portIndex) const
{
	switch (portType)
	{
		case PortType::In:
			if (portIndex == 0)
				return QStringLiteral("Input Curves");
			else if (portIndex == 1)
				return QStringLiteral("Attractor Curves");
			break;

		case PortType::Out:
				return QStringLiteral("Result");

		default:
			break;
	}
	return QString();
}

unsigned int ClumpCurveOperatorModel::nPorts(PortType portType) const
{
	unsigned int result = 1;

	switch (portType)
	{
		case PortType::In:
			result = 2;
			break;

		case PortType::Out:
			result = 1;

		default:
			break;
	}

	return result;
}

NodeDataType ClumpCurveOperatorModel::dataType(PortType, PortIndex) const
{
	return CurvesData().type();
}

void ClumpCurveOperatorModel::setInData(std::shared_ptr<NodeData> nodeData, PortIndex portIndex)
{
	std::shared_ptr<CurvesData> data;

	if(nodeData)
	{
		auto data = std::static_pointer_cast<CurvesData>(nodeData);
		if (portIndex == 0)
		{
			_nodeData = data;
		}
		else if (portIndex == 1)
		{
			m_clumpNodeData = data;
		}

		if (_nodeData && m_clumpNodeData)
			updateCurves();
	}
	else
	{
		m_curves = Curves();
		m_clumpCurves = Curves();
		// clear ssbo???
		emit dataUpdated(0);
	}
}

void ClumpCurveOperatorModel::resetCurves()
{
	AbstractCurveOperatorModel::resetCurves();

	switch (m_clumpNodeData->curveType())
	{
		case CPU:
			m_clumpCurves = m_clumpNodeData->curves();
			break;

		case SSBO:
			ComputeShaderManager::getInstance()->copyCurvesSSBO(m_clumpNodeData->curvesSSBO(), m_clumpCurvesSSBO);
			break;
	}
}

void ClumpCurveOperatorModel::operateCurves()
{
	auto curveType = std::static_pointer_cast<CurvesData>(_nodeData)->curveType();
	auto clumpCurveType = std::static_pointer_cast<CurvesData>(m_clumpNodeData)->curveType();

	if (curveType == SSBO && clumpCurveType == SSBO)
	{
		std::cout<<"processing clump curves SSBO: "<<m_curvesSSBO<<" & "<<m_clumpCurvesSSBO<<"\n";
		ComputeShaderManager::getInstance()->clumpCurvesOperator(m_curvesSSBO, m_clumpCurvesSSBO);
	}
	else
	{
		std::cout<<"invalid curve types for clumping, SSBO only\n";
	}
}
