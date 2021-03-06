#ifndef BENDCURVEOPERATORMODEL_H
#define BENDCURVEOPERATORMODEL_H

#include "AbstractCurveOperatorModel.h"

#include <QtWidgets/QDoubleSpinBox>

class BendCurveOperatorModel : public AbstractCurveOperatorModel
{
	Q_OBJECT

	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief constructor
		//----------------------------------------------------------------------------------------------------------------------
		BendCurveOperatorModel();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief destructor
		//----------------------------------------------------------------------------------------------------------------------
		~BendCurveOperatorModel();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief overrides for NodeDataModel
		//----------------------------------------------------------------------------------------------------------------------
		QString caption() const override {return QString("Bend Curves");};
		//----------------------------------------------------------------------------------------------------------------------
		QString name() const override {return QString("Bend Curves");};
		//----------------------------------------------------------------------------------------------------------------------
		std::unique_ptr<NodeDataModel> clone() const override {return std::make_unique<BendCurveOperatorModel>();};
		//----------------------------------------------------------------------------------------------------------------------
		virtual QString modelName() const {return QString("Bend Operated Curves");};
		//----------------------------------------------------------------------------------------------------------------------
		QWidget* embeddedWidget() override {return m_spinbox;};
		//----------------------------------------------------------------------------------------------------------------------
		QJsonObject save() const override;
		//----------------------------------------------------------------------------------------------------------------------
		void restore(QJsonObject const &p) override;
		//----------------------------------------------------------------------------------------------------------------------

	private:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief manipulate curves
		//----------------------------------------------------------------------------------------------------------------------
		void operateCurves() override;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief spinbox to control intensity (temporary)
		//----------------------------------------------------------------------------------------------------------------------
		QDoubleSpinBox* m_spinbox;

};

#endif // BENDCURVEOPERATORMODEL_H
