/********************************************************************************
** Form generated from reading UI file 'MeshRendererModelWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MESHRENDERERMODELWIDGET_H
#define MESHRENDERERMODELWIDGET_H

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
    QLabel *visibilityLabel;
    QCheckBox *visibilityCheckBox;
    QLabel *roughnessLabel;
    QLabel *metallicLabel;
    QDoubleSpinBox *roughnessDoubleSpinBox;
    QDoubleSpinBox *metallicDoubleSpinBox;

    void setupUi(QWidget *MeshRendererModelWidget)
    {
        if (MeshRendererModelWidget->objectName().isEmpty())
            MeshRendererModelWidget->setObjectName(QStringLiteral("MeshRendererModelWidget"));
        MeshRendererModelWidget->resize(145, 201);
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

        visibilityLabel = new QLabel(MeshRendererModelWidget);
        visibilityLabel->setObjectName(QStringLiteral("visibilityLabel"));

        formLayout->setWidget(5, QFormLayout::LabelRole, visibilityLabel);

        visibilityCheckBox = new QCheckBox(MeshRendererModelWidget);
        visibilityCheckBox->setObjectName(QStringLiteral("visibilityCheckBox"));
        visibilityCheckBox->setChecked(true);

        formLayout->setWidget(5, QFormLayout::FieldRole, visibilityCheckBox);

        roughnessLabel = new QLabel(MeshRendererModelWidget);
        roughnessLabel->setObjectName(QStringLiteral("roughnessLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, roughnessLabel);

        metallicLabel = new QLabel(MeshRendererModelWidget);
        metallicLabel->setObjectName(QStringLiteral("metallicLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, metallicLabel);

        roughnessDoubleSpinBox = new QDoubleSpinBox(MeshRendererModelWidget);
        roughnessDoubleSpinBox->setObjectName(QStringLiteral("roughnessDoubleSpinBox"));
        roughnessDoubleSpinBox->setMaximum(1);
        roughnessDoubleSpinBox->setSingleStep(0.1);
        roughnessDoubleSpinBox->setValue(0.5);

        formLayout->setWidget(3, QFormLayout::FieldRole, roughnessDoubleSpinBox);

        metallicDoubleSpinBox = new QDoubleSpinBox(MeshRendererModelWidget);
        metallicDoubleSpinBox->setObjectName(QStringLiteral("metallicDoubleSpinBox"));
        metallicDoubleSpinBox->setMaximum(1);
        metallicDoubleSpinBox->setSingleStep(0.1);
        metallicDoubleSpinBox->setValue(0.5);

        formLayout->setWidget(4, QFormLayout::FieldRole, metallicDoubleSpinBox);


        retranslateUi(MeshRendererModelWidget);

        QMetaObject::connectSlotsByName(MeshRendererModelWidget);
    } // setupUi

    void retranslateUi(QWidget *MeshRendererModelWidget)
    {
        MeshRendererModelWidget->setWindowTitle(QApplication::translate("MeshRendererModelWidget", "Form", Q_NULLPTR));
        redAmountLabel->setText(QApplication::translate("MeshRendererModelWidget", "Red", Q_NULLPTR));
        greenAmountLabel->setText(QApplication::translate("MeshRendererModelWidget", "Green", Q_NULLPTR));
        blueAmountLabel->setText(QApplication::translate("MeshRendererModelWidget", "Blue", Q_NULLPTR));
        visibilityLabel->setText(QApplication::translate("MeshRendererModelWidget", "Visibility", Q_NULLPTR));
        visibilityCheckBox->setText(QString());
        roughnessLabel->setText(QApplication::translate("MeshRendererModelWidget", "Roughness", Q_NULLPTR));
        metallicLabel->setText(QApplication::translate("MeshRendererModelWidget", "Metalness", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MeshRendererModelWidget: public Ui_MeshRendererModelWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MESHRENDERERMODELWIDGET_H
