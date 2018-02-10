#include "ObjMeshModel.h"

#include "MeshData.h"

#include <QtCore/QEvent>
#include <QtCore/QDir>

#include <QtWidgets/QFileDialog>

#include <fstream>
#include <sstream>
#include <boost/algorithm/string/predicate.hpp>


ObjMeshModel::ObjMeshModel() :
	m_label(new QLabel("Double click to load obj"))
{
	m_label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	QFont f = m_label->font();
	// f.setBold(true);
	// f.setItalic(true);
	m_label->setFont(f);
	m_label->setFixedSize(200, 50);
	m_label->setWordWrap(true);
	m_label->installEventFilter(this);
	m_meshLoaded = false;
	m_mesh = Mesh();
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
	if (object == m_label)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QString fileName = QFileDialog::getOpenFileName(
				nullptr, tr("Load Obj"),
				QDir::currentPath() + "/meshes",
				tr("Mesh Files (*.obj)"));

			m_label->setText(fileName);

			m_meshLoaded = loadObj(fileName);
			if(m_meshLoaded) //obj was loaded successfully
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
	return std::make_shared<MeshData>(m_mesh);
}

QJsonObject ObjMeshModel::save() const
{
	QJsonObject modelJson = NodeDataModel::save();

	if (m_meshLoaded)
		modelJson["label"] = QString(m_label->text());

	return modelJson;
}

void ObjMeshModel::restore(QJsonObject const &p)
{
	QJsonValue v = p["label"];

	if (!v.isUndefined())
	{
		QString fileName = v.toString();
		m_label->setText(fileName);
		m_meshLoaded = loadObj(fileName);
		if(m_meshLoaded) //obj was loaded successfully
			emit dataUpdated(0);
	}
}


bool ObjMeshModel::loadObj(QString _file)
{
	std::ifstream file(_file.toStdString());

	if (!file.is_open())
		return false;

	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uv;
	std::vector<glm::vec3> temp_normal;
	std::vector<Face> temp_faces;

	unsigned int vertCount = 0;
	unsigned int uvCount = 0;
	unsigned int normalCount = 0;
	unsigned int faceCount = 0;

	std::string curline;
	while (std::getline(file, curline))
	{
		if (boost::algorithm::starts_with(curline, "v "))
		{
			vertCount++;
			std::istringstream s(curline.substr(2));
			glm::vec3 v; s >> v.x; s >> v.y; s >> v.z;
			temp_vertices.push_back(v);
		}
		else if (boost::algorithm::starts_with(curline, "vt"))
		{
			uvCount++;
			std::istringstream s(curline.substr(3));
			glm::vec2 uv; s >> uv.x; s >> uv.y;
			temp_uv.push_back(uv);
		}
		else if (boost::algorithm::starts_with(curline, "vn"))
		{
			normalCount++;
			std::istringstream s(curline.substr(2));
			glm::vec3 normal; s >> normal.x; s >> normal.y; s >> normal.z;
			temp_normal.push_back(normal);
		}
		else if (boost::algorithm::starts_with(curline, "f"))
		{
			faceCount++;
			Face temp_face;
			int matches = sscanf((curline.substr(2)).c_str(),
				"%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&temp_face.pos[0], &temp_face.uv[0], &temp_face.normal[0],
				&temp_face.pos[1], &temp_face.uv[1], &temp_face.normal[1],
				&temp_face.pos[2], &temp_face.uv[2], &temp_face.normal[2]
				);
			if (matches != 9)
			{
				std::cout<<"faces can't be read\n";
				return false;
			}
			// decrement as we were 1-indexed
			temp_face.pos[0]--; temp_face.uv[0]--; temp_face.normal[0]--;
			temp_face.pos[1]--; temp_face.uv[1]--; temp_face.normal[1]--;
			temp_face.pos[2]--; temp_face.uv[2]--; temp_face.normal[2]--;
			temp_faces.push_back(temp_face);
		}
		else if (boost::algorithm::starts_with(curline, "#"))
		{
			// pass
		}
	}

	file.close();

	std::cout<<"vertex count: "<<vertCount<<"\n";
	std::cout<<"uv count: "<<uvCount<<"\n";
	std::cout<<"normal count: "<<normalCount<<"\n";
	std::cout<<"face count: "<<faceCount<<"\n";

	m_mesh = Mesh(temp_vertices, temp_uv, temp_normal, temp_faces);

	return true;
}

