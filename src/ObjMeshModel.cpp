#include "ObjMeshModel.h"

#include "MeshData.h"

#include <QtCore/QEvent>
#include <QtCore/QDir>

#include <QtWidgets/QFileDialog>

#include <fstream>

ObjMeshModel::ObjMeshModel() :
	_label(new QLabel("Double click to load obj"))
{
	_label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	QFont f = _label->font();
	// f.setBold(true);
	// f.setItalic(true);
	_label->setFont(f);
	_label->setFixedSize(200, 50);
	_label->setWordWrap(true);
	_label->installEventFilter(this);
}

unsigned int ObjMeshModel::nPorts(PortType portType) const
{
	unsigned int result = 1;

	switch (portType)
	{
		case PortType::In:
			result = 0;
			break;

		case PortType::Out:
			result = 1;
			break;

		default:
			break;
	}

	return result;
}

bool ObjMeshModel::eventFilter(QObject *object, QEvent *event)
{
	if (object == _label)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QString fileName = QFileDialog::getOpenFileName(
				nullptr, tr("Load Obj"),
				QDir::currentPath(),
				tr("Mesh Files (*.obj)"));

			_label->setText(fileName);

			// TODO: load obj to _mesh
			if(loadObj(fileName)) //obj was loaded successfully
				emit dataUpdated(0);

			return true;
		}
	}
	return false;
}

NodeDataType ObjMeshModel::dataType(PortType, PortIndex) const
{
	return MeshData().type();
}

std::shared_ptr<NodeData> ObjMeshModel::outData(PortIndex)
{
	return std::make_shared<MeshData>(_mesh);
}

bool ObjMeshModel::loadObj(QString _file)
{
	std::ifstream file(_file.toStdString());

	if (!file.is_open())
		return false;

	Mesh tempMesh;
}

