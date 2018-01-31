#include "MeshRendererModel.h"

#include <QtCore/QEvent>
#include <QtCore/QDir>

#include <QtWidgets/QFileDialog>

#include "MeshData.h"

MeshRendererModel::MeshRendererModel() :
	m_label(new QLabel(""))
{
	m_label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	QFont f = m_label->font();
	// f.setBold(true);
	// f.setItalic(true);
	m_label->setFont(f);
	m_label->installEventFilter(this);

	m_meshRenderable = MeshRenderable();
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
	if (object == m_label)
	{
		// std::cout<<"MeshRendererModel::eventFilter\n";
	}

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

	if (_nodeData)
	{
		// construct the MeshRenderable
		// std::cout<<"MeshRendererModel::setInData _nodeData\n";
		auto d = std::dynamic_pointer_cast<MeshData>(_nodeData);
		m_meshRenderable = MeshRenderable(d->mesh());
	}
	else
	{
		// delete the VAOS?
		// std::cout<<"MeshRendererModel::setInData ELSE\n";
	}
}
