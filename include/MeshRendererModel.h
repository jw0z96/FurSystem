#ifndef MESHRENDERERMODEL_H
#define MESHRENDERERMODEL_H

#include "MeshRenderable.h"

#include "widgets/MeshRendererModelWidget.h"

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
		~MeshRendererModel();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief overrides for NodeDataModel
		//----------------------------------------------------------------------------------------------------------------------
		QString caption() const override {return QString("Draw Mesh");};
		//----------------------------------------------------------------------------------------------------------------------
		QString name() const override {return QString("Mesh Renderer");};
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
		QWidget* embeddedWidget() override {return m_embedded;};
		//----------------------------------------------------------------------------------------------------------------------
		bool resizable() const override {return false;};

	public slots:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief set the colour of our renderable
		//----------------------------------------------------------------------------------------------------------------------
		void setColour();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief set the visibility of our renderable
		//----------------------------------------------------------------------------------------------------------------------
		void setVisibility();

	protected:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief event filter gets whether we clicked in the node
		//----------------------------------------------------------------------------------------------------------------------
		bool eventFilter(QObject *object, QEvent *event) override;

	private:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief renderable mesh object
		//----------------------------------------------------------------------------------------------------------------------
		std::shared_ptr<MeshRenderable> m_meshRenderable;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief node data
		//----------------------------------------------------------------------------------------------------------------------
		std::shared_ptr<NodeData> _nodeData;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_embedded, m_ui our qt ui widget and contents from the ui file
		//----------------------------------------------------------------------------------------------------------------------
		QWidget* m_embedded;
		Ui::MeshRendererModelWidget* m_ui;
};

#endif // MESHRENDERERMODEL_H
