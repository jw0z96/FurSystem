#include "DistributorModel.h"

#include <QtCore/QEvent>

#include "MeshData.h"
#include "CurvesData.h"

DistributorModel::DistributorModel()
{
	m_curves = Curves();
	for (int i = 0; i < 10; ++i)
	{
		Curve curve;
		for (int j = 0; j < 5; ++j)
		{
			curve.vertices[j] = glm::vec3((i + j) / 10.0, i / 10.0, (i - j * j) / 10.0);
		}
		m_curves.m_curves.push_back(curve);
	}
}

DistributorModel::~DistributorModel() {}

unsigned int DistributorModel::nPorts(PortType portType) const
{
	unsigned int result = 1;

	switch (portType)
	{
		case PortType::In:
			result = 1;
			break;

		case PortType::Out:
			result = 1;

		default:
			break;
	}

	return result;
}

bool DistributorModel::eventFilter(QObject *object, QEvent *event)
{
	return false;
}

NodeDataType DistributorModel::dataType(PortType portType, PortIndex portIndex) const
{
	switch (portType)
	{
		case PortType::In:
			switch (portIndex)
			{
				case 0:
					return MeshData().type();
			}
			break;

		case PortType::Out:
			switch (portIndex)
			{
				case 0:
					return CurvesData().type();
			}
			break;

		case PortType::None:
			break;
	}
	// FIXME: control may reach end of non-void function [-Wreturn-type]
	return NodeDataType();
}

std::shared_ptr<NodeData> DistributorModel::outData(PortIndex)
{
	return std::make_shared<CurvesData>(m_curves);
}

void DistributorModel::setInData(std::shared_ptr<NodeData> nodeData, PortIndex)
{
	_nodeData = nodeData;

	if (_nodeData) // connected or updated
	{
		m_mesh = std::static_pointer_cast<MeshData>(_nodeData)->mesh();
		distribute();
	}
	else // disconnected
	{
		m_curves.m_curves.clear();
		m_mesh = Mesh();
	}

	emit dataUpdated(0);
}

void DistributorModel::distribute()
{
	m_curves.m_curves.clear();

	for (auto face : m_mesh.m_faces)
	{
		glm::vec3 basePos = m_mesh.m_vertexPositions[face.pos[0]];
		basePos += m_mesh.m_vertexPositions[face.pos[1]];
		basePos += m_mesh.m_vertexPositions[face.pos[2]];
		basePos /= 3.0;

		glm::vec3 baseNorm = m_mesh.m_vertexNormals[face.normal[0]];
		baseNorm += m_mesh.m_vertexNormals[face.normal[1]];
		baseNorm += m_mesh.m_vertexNormals[face.normal[2]];
		baseNorm = glm::normalize(baseNorm);

		Curve curve;
		for (int j = 0; j < 5; ++j)
		{
			curve.vertices[j] = basePos + (float(j) * baseNorm * 0.1f);
		}
		m_curves.m_curves.push_back(curve);
	}

}
