/********************************************************************************
** Form generated from reading UI file 'ClumpCurveOperatorModelWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CLUMPCURVEOPERATORMODELWIDGET_H
#define CLUMPCURVEOPERATORMODELWIDGET_H

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

class Ui_ClumpCurveOperatorModelWidget
{
public:
    QFormLayout *formLayout;
    QLabel *envelopeLabel;
    QDoubleSpinBox *envelopeSpinBox;
    QLabel *preserveLengthLabel;
    QCheckBox *preserveLengthCheckBox;

    void setupUi(QWidget *ClumpCurveOperatorModelWidget)
    {
        if (ClumpCurveOperatorModelWidget->objectName().isEmpty())
            ClumpCurveOperatorModelWidget->setObjectName(QStringLiteral("ClumpCurveOperatorModelWidget"));
        ClumpCurveOperatorModelWidget->resize(176, 56);
        formLayout = new QFormLayout(ClumpCurveOperatorModelWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        envelopeLabel = new QLabel(ClumpCurveOperatorModelWidget);
        envelopeLabel->setObjectName(QStringLiteral("envelopeLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, envelopeLabel);

        envelopeSpinBox = new QDoubleSpinBox(ClumpCurveOperatorModelWidget);
        envelopeSpinBox->setObjectName(QStringLiteral("envelopeSpinBox"));
        envelopeSpinBox->setMinimum(0);
        envelopeSpinBox->setMaximum(1);
        envelopeSpinBox->setSingleStep(0.1);
        envelopeSpinBox->setValue(1);

        formLayout->setWidget(0, QFormLayout::FieldRole, envelopeSpinBox);

        preserveLengthLabel = new QLabel(ClumpCurveOperatorModelWidget);
        preserveLengthLabel->setObjectName(QStringLiteral("preserveLengthLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, preserveLengthLabel);

        preserveLengthCheckBox = new QCheckBox(ClumpCurveOperatorModelWidget);
        preserveLengthCheckBox->setObjectName(QStringLiteral("preserveLengthCheckBox"));
        preserveLengthCheckBox->setChecked(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, preserveLengthCheckBox);


        retranslateUi(ClumpCurveOperatorModelWidget);

        QMetaObject::connectSlotsByName(ClumpCurveOperatorModelWidget);
    } // setupUi

    void retranslateUi(QWidget *ClumpCurveOperatorModelWidget)
    {
        ClumpCurveOperatorModelWidget->setWindowTitle(QApplication::translate("ClumpCurveOperatorModelWidget", "Form", Q_NULLPTR));
        envelopeLabel->setText(QApplication::translate("ClumpCurveOperatorModelWidget", "Envelope", Q_NULLPTR));
        preserveLengthLabel->setText(QApplication::translate("ClumpCurveOperatorModelWidget", "Preserve Length", Q_NULLPTR));
        preserveLengthCheckBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ClumpCurveOperatorModelWidget: public Ui_ClumpCurveOperatorModelWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CLUMPCURVEOPERATORMODELWIDGET_H
