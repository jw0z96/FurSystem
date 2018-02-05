#ifndef DISTRIBUTORMODEL_H
#define DISTRIBUTORMODEL_H

#include "Curves.h"

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

class DistributorModel : public NodeDataModel
{
	Q_OBJECT

	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief constructor
		//----------------------------------------------------------------------------------------------------------------------
		DistributorModel();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief destructor
		//----------------------------------------------------------------------------------------------------------------------
		~DistributorModel();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief overrides for NodeDataModel
		//----------------------------------------------------------------------------------------------------------------------
		QString caption() const override {return QString("Disribute curves on Mesh");};
		//----------------------------------------------------------------------------------------------------------------------
		QString name() const override {return QString("DistributorModel");};
		//----------------------------------------------------------------------------------------------------------------------
		std::unique_ptr<NodeDataModel> clone() const override {return std::make_unique<DistributorModel>();};
		//----------------------------------------------------------------------------------------------------------------------
		virtual QString modelName() const {return QString("Distributed Curves");};
		//----------------------------------------------------------------------------------------------------------------------
		unsigned int nPorts(PortType portType) const override;
		//----------------------------------------------------------------------------------------------------------------------
		NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
		//----------------------------------------------------------------------------------------------------------------------
		std::shared_ptr<NodeData> outData(PortIndex port) override;
		//----------------------------------------------------------------------------------------------------------------------
		void setInData(std::shared_ptr<NodeData> nodeData, PortIndex port) override;
		//----------------------------------------------------------------------------------------------------------------------
		QWidget* embeddedWidget() override {return nullptr;};
		//----------------------------------------------------------------------------------------------------------------------
		bool resizable() const override {return false;};

	protected:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief event filter gets whether we clicked in the node
		//----------------------------------------------------------------------------------------------------------------------
		bool eventFilter(QObject *object, QEvent *event) override;

	private:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief curves object
		//----------------------------------------------------------------------------------------------------------------------
		Curves m_curves;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief node data
		//----------------------------------------------------------------------------------------------------------------------
		std::shared_ptr<NodeData> _nodeData;
};

#endif // MESHRENDERERMODEL_H