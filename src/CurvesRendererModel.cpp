#include "CurvesRendererModel.h"

#include <QtCore/QEvent>
#include <QtCore/QDir>

#include "CurvesData.h"
#include "RenderableManager.h"

CurvesRendererModel::CurvesRendererModel() :
	m_embedded(new QWidget()),
	m_ui(new Ui::MeshRendererModelWidget())
{
	// setup ui
	m_ui->setupUi(m_embedded);
	// auto style = nodeStyle();
	// connect colour controls
	connect(m_ui->redAmountDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setColour()));
	connect(m_ui->greenAmountDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setColour()));
	connect(m_ui->blueAmountDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setColour()));

	m_curvesRenderable = std::make_shared<CurvesRenderable>();
}

CurvesRendererModel::~CurvesRendererModel()
{
	std::cout<<"~CurvesRendererModel, setting "<<m_curvesRenderable<<" to be deleted\n";
	m_curvesRenderable->setToBeDeleted();
	delete m_ui;
	// delete m_embedded; // for some reason these cause crash
	// m_embedded->deleteLater();
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
		m_curvesRenderable->setCurves(d->curves());
		m_curvesRenderable->setVisibility(true);
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
