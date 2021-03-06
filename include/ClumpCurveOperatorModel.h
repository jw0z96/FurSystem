#ifndef CLUMPCURVEOPERATORMODEL_H
#define CLUMPCURVEOPERATORMODEL_H

#include "AbstractCurveOperatorModel.h"

#include "widgets/ClumpCurveOperatorModelWidget.h"

class ClumpCurveOperatorModel : public AbstractCurveOperatorModel
{
	Q_OBJECT

	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief constructor
		//----------------------------------------------------------------------------------------------------------------------
		ClumpCurveOperatorModel();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief destructor
		//----------------------------------------------------------------------------------------------------------------------
		~ClumpCurveOperatorModel();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief overrides for NodeDataModel
		//----------------------------------------------------------------------------------------------------------------------
		QString caption() const override {return QString("Clump Curves");};
		//----------------------------------------------------------------------------------------------------------------------
		QString name() const override {return QString("Clump Curves");};
		//----------------------------------------------------------------------------------------------------------------------
		std::unique_ptr<NodeDataModel> clone() const override {return std::make_unique<ClumpCurveOperatorModel>();};
		//----------------------------------------------------------------------------------------------------------------------
		virtual QString modelName() const {return QString("Clump Operated Curves");};
		//----------------------------------------------------------------------------------------------------------------------
		QWidget* embeddedWidget() override {return m_embedded;};
		//----------------------------------------------------------------------------------------------------------------------
		unsigned int nPorts(PortType portType) const override;
		//----------------------------------------------------------------------------------------------------------------------
		void setInData(std::shared_ptr<NodeData> nodeData, PortIndex portIndex) override;
		//----------------------------------------------------------------------------------------------------------------------
		NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
		//----------------------------------------------------------------------------------------------------------------------
		virtual bool portCaptionVisible(PortType, PortIndex) const override {return true;};
		//----------------------------------------------------------------------------------------------------------------------
		virtual QString portCaption(PortType portType, PortIndex portIndex) const override;
		//----------------------------------------------------------------------------------------------------------------------
		QJsonObject save() const override;
		//----------------------------------------------------------------------------------------------------------------------
		void restore(QJsonObject const &p) override;
		//----------------------------------------------------------------------------------------------------------------------

	private:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief reset curves to input state
		//----------------------------------------------------------------------------------------------------------------------
		void resetCurves();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief manipulate curves
		//----------------------------------------------------------------------------------------------------------------------
		void operateCurves() override;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_embedded, m_ui our qt ui widget and contents from the ui file
		//----------------------------------------------------------------------------------------------------------------------
		QWidget* m_embedded;
		Ui::ClumpCurveOperatorModelWidget* m_ui;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief curves SSBO object
		//----------------------------------------------------------------------------------------------------------------------
		unsigned int m_clumpCurvesSSBO;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief curves object
		//----------------------------------------------------------------------------------------------------------------------
		Curves m_clumpCurves;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief node data
		//----------------------------------------------------------------------------------------------------------------------
		std::shared_ptr<CurvesData> m_clumpNodeData;
};

#endif // CLUMPCURVEOPERATORMODEL_H
