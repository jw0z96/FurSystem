#ifndef MESHRENDERERMODEL_H
#define MESHRENDERERMODEL_H

#include "MeshRenderable.h"

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

class MeshRendererModel : public NodeDataModel
{
	Q_OBJECT

	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief constructor
		//----------------------------------------------------------------------------------------------------------------------
		MeshRendererModel();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief destructor
		//----------------------------------------------------------------------------------------------------------------------
		virtual ~MeshRendererModel() {}
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief overrides for NodeDataModel
		//----------------------------------------------------------------------------------------------------------------------
		QString caption() const override {return QString("Draw Mesh");};
		//----------------------------------------------------------------------------------------------------------------------
		QString name() const override {return QString("MeshRendererModel");};
		//----------------------------------------------------------------------------------------------------------------------
		std::unique_ptr<NodeDataModel> clone() const override {return std::make_unique<MeshRendererModel>();};
		//----------------------------------------------------------------------------------------------------------------------
		virtual QString modelName() const {return QString("Rendered Mesh");};
		//----------------------------------------------------------------------------------------------------------------------
		unsigned int nPorts(PortType portType) const override;
		//----------------------------------------------------------------------------------------------------------------------
		NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
		//----------------------------------------------------------------------------------------------------------------------
		std::shared_ptr<NodeData> outData(PortIndex port) override;
		//----------------------------------------------------------------------------------------------------------------------
		void setInData(std::shared_ptr<NodeData> nodeData, PortIndex port) override;
		//----------------------------------------------------------------------------------------------------------------------
		QWidget* embeddedWidget() override {return m_label;};
		// QWidget* embeddedWidget() override {return NULL;};
		//----------------------------------------------------------------------------------------------------------------------
		bool resizable() const override {return false;};

	protected:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief event filter gets whether we clicked in the node
		//----------------------------------------------------------------------------------------------------------------------
		bool eventFilter(QObject *object, QEvent *event) override;

	private:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief label
		//----------------------------------------------------------------------------------------------------------------------
		QLabel* m_label;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief renderable mesh object
		//----------------------------------------------------------------------------------------------------------------------
		MeshRenderable m_meshRenderable;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief node data
		//----------------------------------------------------------------------------------------------------------------------
		std::shared_ptr<NodeData> _nodeData;
};

#endif // MESHRENDERERMODEL_H
