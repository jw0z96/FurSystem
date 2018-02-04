/********************************************************************************
** Form generated from reading UI file 'MeshRendererModelWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MESHRENDERERMODELWIDGET_H
#define MESHRENDERERMODELWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeshRendererModelWidget
{
public:
    QFormLayout *formLayout;
    QLabel *redAmountLabel;
    QDoubleSpinBox *redAmountDoubleSpinBox;
    QLabel *greenAmountLabel;
    QDoubleSpinBox *greenAmountDoubleSpinBox;
    QLabel *blueAmountLabel;
    QDoubleSpinBox *blueAmountDoubleSpinBox;

    void setupUi(QWidget *MeshRendererModelWidget)
    {
        if (MeshRendererModelWidget->objectName().isEmpty())
            MeshRendererModelWidget->setObjectName(QStringLiteral("MeshRendererModelWidget"));
        MeshRendererModelWidget->resize(125, 97);
        formLayout = new QFormLayout(MeshRendererModelWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        redAmountLabel = new QLabel(MeshRendererModelWidget);
        redAmountLabel->setObjectName(QStringLiteral("redAmountLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, redAmountLabel);

        redAmountDoubleSpinBox = new QDoubleSpinBox(MeshRendererModelWidget);
        redAmountDoubleSpinBox->setObjectName(QStringLiteral("redAmountDoubleSpinBox"));
        redAmountDoubleSpinBox->setMaximum(1);
        redAmountDoubleSpinBox->setSingleStep(0.1);
        redAmountDoubleSpinBox->setValue(1);

        formLayout->setWidget(0, QFormLayout::FieldRole, redAmountDoubleSpinBox);

        greenAmountLabel = new QLabel(MeshRendererModelWidget);
        greenAmountLabel->setObjectName(QStringLiteral("greenAmountLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, greenAmountLabel);

        greenAmountDoubleSpinBox = new QDoubleSpinBox(MeshRendererModelWidget);
        greenAmountDoubleSpinBox->setObjectName(QStringLiteral("greenAmountDoubleSpinBox"));
        greenAmountDoubleSpinBox->setMaximum(1);
        greenAmountDoubleSpinBox->setSingleStep(0.1);

        formLayout->setWidget(1, QFormLayout::FieldRole, greenAmountDoubleSpinBox);

        blueAmountLabel = new QLabel(MeshRendererModelWidget);
        blueAmountLabel->setObjectName(QStringLiteral("blueAmountLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, blueAmountLabel);

        blueAmountDoubleSpinBox = new QDoubleSpinBox(MeshRendererModelWidget);
        blueAmountDoubleSpinBox->setObjectName(QStringLiteral("blueAmountDoubleSpinBox"));
        blueAmountDoubleSpinBox->setMaximum(1);
        blueAmountDoubleSpinBox->setSingleStep(0.1);

        formLayout->setWidget(2, QFormLayout::FieldRole, blueAmountDoubleSpinBox);


        retranslateUi(MeshRendererModelWidget);

        QMetaObject::connectSlotsByName(MeshRendererModelWidget);
    } // setupUi

    void retranslateUi(QWidget *MeshRendererModelWidget)
    {
        MeshRendererModelWidget->setWindowTitle(QApplication::translate("MeshRendererModelWidget", "Form", Q_NULLPTR));
        redAmountLabel->setText(QApplication::translate("MeshRendererModelWidget", "Red", Q_NULLPTR));
        greenAmountLabel->setText(QApplication::translate("MeshRendererModelWidget", "Green", Q_NULLPTR));
        blueAmountLabel->setText(QApplication::translate("MeshRendererModelWidget", "Blue", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MeshRendererModelWidget: public Ui_MeshRendererModelWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MESHRENDERERMODELWIDGET_H
