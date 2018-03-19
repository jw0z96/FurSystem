#include "CurvesRendererModel.h"

#include <QtCore/QEvent>
#include <QtCore/QDir>

#include "CurvesData.h"
#include "RenderableManager.h"

CurvesRendererModel::CurvesRendererModel() :
	m_embedded(new QWidget()),
	m_ui(new Ui::CurvesRendererModelWidget())
{
	// setup ui
	m_ui->setupUi(m_embedded);
	// auto style = nodeStyle();
	// connect colour & visibiliy controls
	connect(m_ui->redAmountDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setColour()));
	connect(m_ui->greenAmountDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setColour()));
	connect(m_ui->blueAmountDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setColour()));
	connect(m_ui->widthDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setWidth()));
	connect(m_ui->roughnessDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setMetallicRoughness()));
	connect(m_ui->metallicDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setMetallicRoughness()));
	connect(m_ui->ribbonsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setRenderType()));
	connect(m_ui->visibilityCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setVisibility()));
	m_curvesRenderable = std::make_shared<CurvesRenderable>();
}

CurvesRendererModel::~CurvesRendererModel()
{
	// std::cout<<"~CurvesRendererModel, setting "<<m_curvesRenderable<<" to be deleted\n";
	m_curvesRenderable->setToBeDeleted();
	delete m_ui;
	// delete m_embedded; // for some reason these cause crash
	// m_embedded->deleteLater();
}

QJsonObject CurvesRendererModel::save() const
{
	QJsonObject modelJson = NodeDataModel::save();

	modelJson["red"] = m_ui->redAmountDoubleSpinBox->value();
	modelJson["green"] = m_ui->greenAmountDoubleSpinBox->value();
	modelJson["blue"] = m_ui->blueAmountDoubleSpinBox->value();
	modelJson["width"] = m_ui->widthDoubleSpinBox->value();
	modelJson["roughness"] = m_ui->roughnessDoubleSpinBox->value();
	modelJson["metallic"] = m_ui->metallicDoubleSpinBox->value();
	modelJson["ribbons"] = m_ui->ribbonsCheckBox->isChecked();
	modelJson["visibiliy"] = m_ui->visibilityCheckBox->isChecked();

	return modelJson;
}

void CurvesRendererModel::restore(QJsonObject const &p)
{
	QJsonValue r = p["red"];
	if (!r.isUndefined())
		m_ui->redAmountDoubleSpinBox->setValue(r.toDouble());

	QJsonValue g = p["green"];
	if (!g.isUndefined())
		m_ui->greenAmountDoubleSpinBox->setValue(g.toDouble());

	QJsonValue b = p["blue"];
	if (!b.isUndefined())
		m_ui->blueAmountDoubleSpinBox->setValue(b.toDouble());

	QJsonValue w = p["width"];
	if (!w.isUndefined())
		m_ui->widthDoubleSpinBox->setValue(w.toDouble());

	QJsonValue ro = p["roughness"];
	if (!ro.isUndefined())
		m_ui->roughnessDoubleSpinBox->setValue(ro.toDouble());

	QJsonValue m = p["metallic"];
	if (!m.isUndefined())
		m_ui->metallicDoubleSpinBox->setValue(m.toDouble());

	QJsonValue ri = p["ribbons"];
	if (!ri.isUndefined())
		m_ui->ribbonsCheckBox->setChecked(ri.toBool());

	QJsonValue v = p["visibiliy"];
	if (!v.isUndefined())
		m_ui->visibilityCheckBox->setChecked(v.toBool());
}

unsigned int CurvesRendererModel::nPorts(PortType portType) const
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

bool CurvesRendererModel::eventFilter(QObject *object, QEvent *event)
{
	if (object == m_embedded)
		m_embedded->setFocusPolicy(Qt::StrongFocus);
	return false;
}

NodeDataType CurvesRendererModel::dataType(PortType, PortIndex) const
{
	return CurvesData().type();
}

std::shared_ptr<NodeData> CurvesRendererModel::outData(PortIndex)
{
	return _nodeData;
}

void CurvesRendererModel::setInData(std::shared_ptr<NodeData> nodeData, PortIndex)
{
	_nodeData = nodeData;

	if (_nodeData) // connected
	{
		// register the renderable with the RenderableManager if it isn't already
		RenderableManager::getInstance()->registerRenderable(m_curvesRenderable);
		auto d = std::static_pointer_cast<CurvesData>(_nodeData);
		m_curvesRenderable->setCurveType(d->curveType());
		m_curvesRenderable->setCurves(d->curves());
		m_curvesRenderable->setSourceSSBO(d->curvesSSBO());
		m_curvesRenderable->setVisibility(m_ui->visibilityCheckBox->isChecked());
		RenderableManager::getInstance()->updateViewport();
	}
	else // disconnected
	{
		m_curvesRenderable->setVisibility(false);
		RenderableManager::getInstance()->updateViewport();
	}
}

void CurvesRendererModel::setColour()
{
	glm::vec3 col;
	col.x = m_ui->redAmountDoubleSpinBox->value();
	col.y = m_ui->greenAmountDoubleSpinBox->value();
	col.z = m_ui->blueAmountDoubleSpinBox->value();
	m_curvesRenderable->setColour(col);
	RenderableManager::getInstance()->updateViewport();
}

void CurvesRendererModel::setVisibility()
{
	m_curvesRenderable->setVisibility(m_ui->visibilityCheckBox->isChecked());
	RenderableManager::getInstance()->updateViewport();
}

void CurvesRendererModel::setRenderType()
{
	if (m_ui->ribbonsCheckBox->isChecked())
		m_curvesRenderable->setRibbons();
	else
		m_curvesRenderable->setLines();
	RenderableManager::getInstance()->updateViewport();
}

void CurvesRendererModel::setWidth()
{
	m_curvesRenderable->setWidth(m_ui->widthDoubleSpinBox->value());
	RenderableManager::getInstance()->updateViewport();
}

void CurvesRendererModel::setMetallicRoughness()
{
	m_curvesRenderable->setRoughness(m_ui->roughnessDoubleSpinBox->value());
	m_curvesRenderable->setMetallic(m_ui->metallicDoubleSpinBox->value());
	RenderableManager::getInstance()->updateViewport();
}
