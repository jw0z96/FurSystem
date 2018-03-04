#ifndef CURVESRENDERERMODEL_H
#define CURVESRENDERERMODEL_H

#include "CurvesRenderable.h"

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

class CurvesRendererModel : public NodeDataModel
{
	Q_OBJECT

	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief constructor
		//----------------------------------------------------------------------------------------------------------------------
		CurvesRendererModel();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief destructor
		//----------------------------------------------------------------------------------------------------------------------
		~CurvesRendererModel();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief overrides for NodeDataModel
		//----------------------------------------------------------------------------------------------------------------------
		QString caption() const override {return QString("Draw Curves");};
		//----------------------------------------------------------------------------------------------------------------------
		QString name() const override {return QString("Curves Renderer");};
		//----------------------------------------------------------------------------------------------------------------------
		std::unique_ptr<NodeDataModel> clone() const override {return std::make_unique<CurvesRendererModel>();};
		//----------------------------------------------------------------------------------------------------------------------
		virtual QString modelName() const {return QString("Rendered Curves");};
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
		std::shared_ptr<CurvesRenderable> m_curvesRenderable;
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

#endif // CURVESRENDERERMODEL_H
