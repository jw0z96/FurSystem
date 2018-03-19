#include "ClumpCurveOperatorModel.h"

#include "ComputeShaderManager.h"

#include "CurvesData.h"

ClumpCurveOperatorModel::ClumpCurveOperatorModel() :
	AbstractCurveOperatorModel(),
	m_embedded(new QWidget()),
	m_ui(new Ui::ClumpCurveOperatorModelWidget())
{
	// init clump curve variables
	m_clumpCurves = Curves();
	m_clumpCurvesSSBO = 0;
	m_clumpNodeData = nullptr;
	// setup ui
	m_ui->setupUi(m_embedded);
	// connect spinbox and checkbox
	connect(m_ui->envelopeSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateCurves()));
	connect(m_ui->preserveLengthCheckBox, SIGNAL(stateChanged(int)), this, SLOT(updateCurves()));
}

ClumpCurveOperatorModel::~ClumpCurveOperatorModel()
{
	if (m_clumpCurvesSSBO)
		glDeleteBuffers(1, &m_clumpCurvesSSBO);

	delete m_ui;
}

QJsonObject ClumpCurveOperatorModel::save() const
{
	QJsonObject modelJson = NodeDataModel::save();

	modelJson["envelope"] = m_ui->envelopeSpinBox->value();
	modelJson["preserve"] = m_ui->preserveLengthCheckBox->isChecked();

	return modelJson;
}

void ClumpCurveOperatorModel::restore(QJsonObject const &p)
{
	QJsonValue r = p["envelope"];
	if (!r.isUndefined())
		m_ui->envelopeSpinBox->setValue(r.toDouble());

	QJsonValue v = p["preserve"];
	if (!v.isUndefined())
		m_ui->preserveLengthCheckBox->setChecked(v.toBool());
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
	if(_nodeData)
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
}

void ClumpCurveOperatorModel::operateCurves()
{
	if(_nodeData)
	{
		auto curveType = std::static_pointer_cast<CurvesData>(_nodeData)->curveType();
		auto clumpCurveType = std::static_pointer_cast<CurvesData>(m_clumpNodeData)->curveType();

		if (curveType == SSBO && clumpCurveType == SSBO)
		{
			// std::cout<<"processing clump curves SSBO: "<<m_curvesSSBO<<" & "<<m_clumpCurvesSSBO<<"\n";
			ComputeShaderManager::getInstance()->clumpCurvesOperator(m_curvesSSBO, m_clumpCurvesSSBO, m_ui->envelopeSpinBox->value(), m_ui->preserveLengthCheckBox->isChecked());
		}
		else
		{
			std::cout<<"invalid curve types for clumping, SSBO only\n";
		}
	}
}
