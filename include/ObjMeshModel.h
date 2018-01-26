#ifndef OBJMESHMODEL_H
#define OBJMESHMODEL_H

#include "Mesh.h"

#include <iostream>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include "nodeeditor/DataModelRegistry.hpp"
#include "nodeeditor/NodeDataModel.hpp"

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

class ObjMeshModel : public NodeDataModel
{
	Q_OBJECT

	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief constructor
		//----------------------------------------------------------------------------------------------------------------------
		ObjMeshModel();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief destructor
		//----------------------------------------------------------------------------------------------------------------------
		virtual ~ObjMeshModel() {}
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief overrides for NodeDataModel
		//----------------------------------------------------------------------------------------------------------------------
		QString caption() const override {return QString("Load Obj Mesh");};
		//----------------------------------------------------------------------------------------------------------------------
		QString name() const override {return QString("ObjMeshModel");};
		//----------------------------------------------------------------------------------------------------------------------
		std::unique_ptr<NodeDataModel> clone() const override {return std::make_unique<ObjMeshModel>();};
		//----------------------------------------------------------------------------------------------------------------------
		virtual QString modelName() const {return QString("Source Mesh");};
		//----------------------------------------------------------------------------------------------------------------------
		unsigned int nPorts(PortType portType) const override;
		//----------------------------------------------------------------------------------------------------------------------
		NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
		//----------------------------------------------------------------------------------------------------------------------
		std::shared_ptr<NodeData> outData(PortIndex port) override;
		//----------------------------------------------------------------------------------------------------------------------
		void setInData(std::shared_ptr<NodeData>, int) override {};
		//----------------------------------------------------------------------------------------------------------------------
		QWidget* embeddedWidget() override {return _label;};
		//----------------------------------------------------------------------------------------------------------------------
		bool resizable() const override {return true;};

	protected:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief event filter  gets whether we clicked in the node
		//----------------------------------------------------------------------------------------------------------------------
		bool eventFilter(QObject *object, QEvent *event) override;

	private:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief label
		//----------------------------------------------------------------------------------------------------------------------
		QLabel* _label;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief mesh object
		//----------------------------------------------------------------------------------------------------------------------
		Mesh _mesh;
};

#endif // OBJMESHMODEL_H
