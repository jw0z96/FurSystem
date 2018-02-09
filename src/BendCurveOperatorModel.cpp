#include "BendCurveOperatorModel.h"

BendCurveOperatorModel::BendCurveOperatorModel() :
	m_spinbox(new QDoubleSpinBox())
{
	m_spinbox->setRange(0.0, 100.0);
	m_spinbox->setDecimals(3);
	m_spinbox->setSingleStep(0.01);
	m_spinbox->setValue(0.1);

	connect(m_spinbox, SIGNAL(valueChanged(double)), this, SLOT(updateCurves()));

	m_curves = Curves();
}

BendCurveOperatorModel::~BendCurveOperatorModel()
{
	// delete m_spinbox;
}

void BendCurveOperatorModel::operateCurves()
{
	AbstractCurveOperatorModel::resetCurves();

	glm::vec3 bendDirection = glm::vec3(0.0, -1.0, 0.0);

	float intensity = m_spinbox->value();

	for (auto &curve : m_curves.m_curves)
	{
		for (unsigned int j = 1; j < 5; ++j)
		{
			curve.vertices[j] += float(j) * float(j) * intensity * bendDirection;
		}
	}
}