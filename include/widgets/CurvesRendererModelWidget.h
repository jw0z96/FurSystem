/********************************************************************************
** Form generated from reading UI file 'CurvesRendererModelWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CURVESRENDERERMODELWIDGET_H
#define CURVESRENDERERMODELWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CurvesRendererModelWidget
{
public:
    QFormLayout *formLayout;
    QLabel *redAmountLabel;
    QDoubleSpinBox *redAmountDoubleSpinBox;
    QLabel *greenAmountLabel;
    QDoubleSpinBox *greenAmountDoubleSpinBox;
    QLabel *blueAmountLabel;
    QDoubleSpinBox *blueAmountDoubleSpinBox;
    QLabel *visibilityLabel;
    QCheckBox *visibilityCheckBox;
    QLabel *ribbonsLabel;
    QCheckBox *ribbonsCheckBox;
    QLabel *widthLabel;
    QDoubleSpinBox *widthDoubleSpinBox;

    void setupUi(QWidget *CurvesRendererModelWidget)
    {
        if (CurvesRendererModelWidget->objectName().isEmpty())
            CurvesRendererModelWidget->setObjectName(QStringLiteral("CurvesRendererModelWidget"));
        CurvesRendererModelWidget->resize(136, 153);
        formLayout = new QFormLayout(CurvesRendererModelWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        redAmountLabel = new QLabel(CurvesRendererModelWidget);
        redAmountLabel->setObjectName(QStringLiteral("redAmountLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, redAmountLabel);

        redAmountDoubleSpinBox = new QDoubleSpinBox(CurvesRendererModelWidget);
        redAmountDoubleSpinBox->setObjectName(QStringLiteral("redAmountDoubleSpinBox"));
        redAmountDoubleSpinBox->setMaximum(1);
        redAmountDoubleSpinBox->setSingleStep(0.1);
        redAmountDoubleSpinBox->setValue(1);

        formLayout->setWidget(0, QFormLayout::FieldRole, redAmountDoubleSpinBox);

        greenAmountLabel = new QLabel(CurvesRendererModelWidget);
        greenAmountLabel->setObjectName(QStringLiteral("greenAmountLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, greenAmountLabel);

        greenAmountDoubleSpinBox = new QDoubleSpinBox(CurvesRendererModelWidget);
        greenAmountDoubleSpinBox->setObjectName(QStringLiteral("greenAmountDoubleSpinBox"));
        greenAmountDoubleSpinBox->setMaximum(1);
        greenAmountDoubleSpinBox->setSingleStep(0.1);

        formLayout->setWidget(1, QFormLayout::FieldRole, greenAmountDoubleSpinBox);

        blueAmountLabel = new QLabel(CurvesRendererModelWidget);
        blueAmountLabel->setObjectName(QStringLiteral("blueAmountLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, blueAmountLabel);

        blueAmountDoubleSpinBox = new QDoubleSpinBox(CurvesRendererModelWidget);
        blueAmountDoubleSpinBox->setObjectName(QStringLiteral("blueAmountDoubleSpinBox"));
        blueAmountDoubleSpinBox->setMaximum(1);
        blueAmountDoubleSpinBox->setSingleStep(0.1);

        formLayout->setWidget(2, QFormLayout::FieldRole, blueAmountDoubleSpinBox);

        visibilityLabel = new QLabel(CurvesRendererModelWidget);
        visibilityLabel->setObjectName(QStringLiteral("visibilityLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, visibilityLabel);

        visibilityCheckBox = new QCheckBox(CurvesRendererModelWidget);
        visibilityCheckBox->setObjectName(QStringLiteral("visibilityCheckBox"));
        visibilityCheckBox->setChecked(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, visibilityCheckBox);

        ribbonsLabel = new QLabel(CurvesRendererModelWidget);
        ribbonsLabel->setObjectName(QStringLiteral("ribbonsLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, ribbonsLabel);

        ribbonsCheckBox = new QCheckBox(CurvesRendererModelWidget);
        ribbonsCheckBox->setObjectName(QStringLiteral("ribbonsCheckBox"));
        ribbonsCheckBox->setChecked(true);

        formLayout->setWidget(4, QFormLayout::FieldRole, ribbonsCheckBox);

        widthLabel = new QLabel(CurvesRendererModelWidget);
        widthLabel->setObjectName(QStringLiteral("widthLabel"));

        formLayout->setWidget(5, QFormLayout::LabelRole, widthLabel);

        widthDoubleSpinBox = new QDoubleSpinBox(CurvesRendererModelWidget);
        widthDoubleSpinBox->setObjectName(QStringLiteral("widthDoubleSpinBox"));
        widthDoubleSpinBox->setDecimals(3);
        widthDoubleSpinBox->setMaximum(1);
        widthDoubleSpinBox->setSingleStep(0.001);
        widthDoubleSpinBox->setValue(0.005);

        formLayout->setWidget(5, QFormLayout::FieldRole, widthDoubleSpinBox);


        retranslateUi(CurvesRendererModelWidget);

        QMetaObject::connectSlotsByName(CurvesRendererModelWidget);
    } // setupUi

    void retranslateUi(QWidget *CurvesRendererModelWidget)
    {
        CurvesRendererModelWidget->setWindowTitle(QApplication::translate("CurvesRendererModelWidget", "Form", Q_NULLPTR));
        redAmountLabel->setText(QApplication::translate("CurvesRendererModelWidget", "Red", Q_NULLPTR));
        greenAmountLabel->setText(QApplication::translate("CurvesRendererModelWidget", "Green", Q_NULLPTR));
        blueAmountLabel->setText(QApplication::translate("CurvesRendererModelWidget", "Blue", Q_NULLPTR));
        visibilityLabel->setText(QApplication::translate("CurvesRendererModelWidget", "Visibility", Q_NULLPTR));
        visibilityCheckBox->setText(QString());
        ribbonsLabel->setText(QApplication::translate("CurvesRendererModelWidget", "Ribbons", Q_NULLPTR));
        ribbonsCheckBox->setText(QString());
        widthLabel->setText(QApplication::translate("CurvesRendererModelWidget", "Width", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CurvesRendererModelWidget: public Ui_CurvesRendererModelWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CURVESRENDERERMODELWIDGET_H
