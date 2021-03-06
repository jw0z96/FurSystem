#include "NoiseCurveOperatorModel.h"

#include "ComputeShaderManager.h"

#include "CurvesData.h"

NoiseCurveOperatorModel::NoiseCurveOperatorModel() :
	AbstractCurveOperatorModel(),
	m_spinbox(new QDoubleSpinBox())
{
	m_spinbox->setRange(0.0, 1.0);
	m_spinbox->setDecimals(2);
	m_spinbox->setSingleStep(0.1);
	m_spinbox->setValue(1.0);
	connect(m_spinbox, SIGNAL(valueChanged(double)), this, SLOT(updateCurves()));
}

NoiseCurveOperatorModel::~NoiseCurveOperatorModel()
{
	// delete m_spinbox;
}

QJsonObject NoiseCurveOperatorModel::save() const
{
	QJsonObject modelJson = NodeDataModel::save();

	modelJson["value"] = m_spinbox->value();

	return modelJson;
}

void NoiseCurveOperatorModel::restore(QJsonObject const &p)
{
	QJsonValue r = p["value"];
	if (!r.isUndefined())
		m_spinbox->setValue(r.toDouble());
}

void NoiseCurveOperatorModel::operateCurves()
{
	if(_nodeData)
	{
		float intensity = m_spinbox->value();

		if (intensity == 0.0)
			return;

		switch (std::static_pointer_cast<CurvesData>(_nodeData)->curveType())
		{
			case CPU:
				// std::cout<<"processing noise curves not possible on CPU\n";
				break;

			case SSBO:
				// std::cout<<"processing noise curves SSBO\n";
				ComputeShaderManager::getInstance()->noiseCurvesOperator(m_curvesSSBO, intensity);
				break;
		}
	}
}
