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
				QDir::currentPath(),
				tr("Mesh Files (*.obj)"));

			m_label->setText(fileName);

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
	return std::make_shared<MeshData>(m_mesh);
}

bool ObjMeshModel::loadObj(QString _file)
{
	std::ifstream file(_file.toStdString());

	if (!file.is_open())
		return false;

	Mesh tempMesh;
	// tempMesh.m_vertices.clear();
	// tempMesh.m_faces.clear();

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
			// unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
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
			// else
			// {
			// 	std::cout<<"face: "<<vertexIndex[0]<<"/"<<uvIndex[0]<<"/"<<normalIndex[0]<<" "<<vertexIndex[1]<<"/"<<uvIndex[1]<<"/"<<normalIndex[1]<<" "<<vertexIndex[2]<<"/"<<uvIndex[2]<<"/"<<normalIndex[2]<<"\n";
			// }
		}
		else if (boost::algorithm::starts_with(curline, "#"))
		{
			// pass
		}
	}

	std::cout<<"vertex count: "<<vertCount<<"\n";
	std::cout<<"uv count: "<<uvCount<<"\n";
	std::cout<<"normal count: "<<normalCount<<"\n";
	std::cout<<"face count: "<<faceCount<<"\n";
	// for (int i = 0; i < temp_vertices.size(); ++i)
	// {
	// 	std::cout<<i<<": "<<temp_vertices[i].x<<", "<<temp_vertices[i].y<<", "<<temp_vertices[i].z<<"\n";
	// }
	file.close();
	return true;
}

