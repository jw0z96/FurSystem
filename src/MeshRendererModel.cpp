#include "MeshRendererModel.h"

#include <QtCore/QEvent>
#include <QtCore/QDir>

#include "MeshData.h"
#include "RenderableManager.h"

MeshRendererModel::MeshRendererModel() :
	m_embedded(new QWidget()),
	m_ui(new Ui::MeshRendererModelWidget())
{
	// setup ui
	m_ui->setupUi(m_embedded);
	// auto style = nodeStyle();
	// connect colour & visibiliy controls
	connect(m_ui->redAmountDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setColour()));
	connect(m_ui->greenAmountDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setColour()));
	connect(m_ui->blueAmountDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setColour()));
	connect(m_ui->roughnessDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setMetallicRoughness()));
	connect(m_ui->metallicDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setMetallicRoughness()));
	connect(m_ui->visibilityCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setVisibility()));
	m_meshRenderable = std::make_shared<MeshRenderable>();
}

MeshRendererModel::~MeshRendererModel()
{
	std::cout<<"~MeshRendererModel, setting "<<m_meshRenderable<<" to be deleted\n";
	m_meshRenderable->setToBeDeleted();
	delete m_ui;
	// delete m_embedded; // for some reason these cause crash
	// m_embedded->deleteLater();
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
	if (object == m_embedded)
		m_embedded->setFocusPolicy(Qt::StrongFocus);
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
		// register the renderable with the RenderableManager if it isn't already
		RenderableManager::getInstance()->registerRenderable(m_meshRenderable);
		auto d = std::static_pointer_cast<MeshData>(_nodeData);
		m_meshRenderable->setMesh(d->mesh());
		m_meshRenderable->setVisibility(m_ui->visibilityCheckBox->isChecked());
		RenderableManager::getInstance()->updateViewport();
	}
	else // disconnected
	{
		m_meshRenderable->setVisibility(false);
		RenderableManager::getInstance()->updateViewport();
	}
}

void MeshRendererModel::setColour()
{
	glm::vec3 col;
	col.x = m_ui->redAmountDoubleSpinBox->value();
	col.y = m_ui->greenAmountDoubleSpinBox->value();
	col.z = m_ui->blueAmountDoubleSpinBox->value();
	m_meshRenderable->setColour(col);
	RenderableManager::getInstance()->updateViewport();
}

void MeshRendererModel::setVisibility()
{
	m_meshRenderable->setVisibility(m_ui->visibilityCheckBox->isChecked());
	RenderableManager::getInstance()->updateViewport();
}

void MeshRendererModel::setMetallicRoughness()
{
	m_meshRenderable->setRoughness(m_ui->roughnessDoubleSpinBox->value());
	m_meshRenderable->setMetallic(m_ui->metallicDoubleSpinBox->value());
	RenderableManager::getInstance()->updateViewport();
}
