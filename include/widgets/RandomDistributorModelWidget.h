/********************************************************************************
** Form generated from reading UI file 'RandomDistributorModelWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef RANDOMDISTRIBUTORMODELWIDGET_H
#define RANDOMDISTRIBUTORMODELWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RandomDistributorModelWidget
{
public:
    QFormLayout *formLayout;
    QLabel *countLabel;
    QSpinBox *countSpinBox;
    QLabel *modeLabel;
    QCheckBox *modeCheckBox;
    QLabel *lengthLabel;
    QDoubleSpinBox *lengthSpinBox;
    QLabel *variationLabel;
    QDoubleSpinBox *variationSpinBox;

    void setupUi(QWidget *RandomDistributorModelWidget)
    {
        if (RandomDistributorModelWidget->objectName().isEmpty())
            RandomDistributorModelWidget->setObjectName(QStringLiteral("RandomDistributorModelWidget"));
        RandomDistributorModelWidget->resize(152, 114);
        formLayout = new QFormLayout(RandomDistributorModelWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        countLabel = new QLabel(RandomDistributorModelWidget);
        countLabel->setObjectName(QStringLiteral("countLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, countLabel);

        countSpinBox = new QSpinBox(RandomDistributorModelWidget);
        countSpinBox->setObjectName(QStringLiteral("countSpinBox"));
        countSpinBox->setMaximum(999999);
        countSpinBox->setSingleStep(100);
        countSpinBox->setValue(1000);

        formLayout->setWidget(0, QFormLayout::FieldRole, countSpinBox);

        modeLabel = new QLabel(RandomDistributorModelWidget);
        modeLabel->setObjectName(QStringLiteral("modeLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, modeLabel);

        modeCheckBox = new QCheckBox(RandomDistributorModelWidget);
        modeCheckBox->setObjectName(QStringLiteral("modeCheckBox"));
        modeCheckBox->setChecked(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, modeCheckBox);

        lengthLabel = new QLabel(RandomDistributorModelWidget);
        lengthLabel->setObjectName(QStringLiteral("lengthLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, lengthLabel);

        lengthSpinBox = new QDoubleSpinBox(RandomDistributorModelWidget);
        lengthSpinBox->setObjectName(QStringLiteral("lengthSpinBox"));
        lengthSpinBox->setMinimum(0.01);
        lengthSpinBox->setSingleStep(0.1);
        lengthSpinBox->setValue(1);

        formLayout->setWidget(1, QFormLayout::FieldRole, lengthSpinBox);

        variationLabel = new QLabel(RandomDistributorModelWidget);
        variationLabel->setObjectName(QStringLiteral("variationLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, variationLabel);

        variationSpinBox = new QDoubleSpinBox(RandomDistributorModelWidget);
        variationSpinBox->setObjectName(QStringLiteral("variationSpinBox"));
        variationSpinBox->setMinimum(0);
        variationSpinBox->setMaximum(1);
        variationSpinBox->setSingleStep(0.1);
        variationSpinBox->setValue(0);

        formLayout->setWidget(2, QFormLayout::FieldRole, variationSpinBox);


        retranslateUi(RandomDistributorModelWidget);

        QMetaObject::connectSlotsByName(RandomDistributorModelWidget);
    } // setupUi

    void retranslateUi(QWidget *RandomDistributorModelWidget)
    {
        RandomDistributorModelWidget->setWindowTitle(QApplication::translate("RandomDistributorModelWidget", "Form", Q_NULLPTR));
        countLabel->setText(QApplication::translate("RandomDistributorModelWidget", "Amount", Q_NULLPTR));
        modeLabel->setText(QApplication::translate("RandomDistributorModelWidget", "Mode", Q_NULLPTR));
        modeCheckBox->setText(QApplication::translate("RandomDistributorModelWidget", "GPU", Q_NULLPTR));
        lengthLabel->setText(QApplication::translate("RandomDistributorModelWidget", "Length", Q_NULLPTR));
        variationLabel->setText(QApplication::translate("RandomDistributorModelWidget", "Variation", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RandomDistributorModelWidget: public Ui_RandomDistributorModelWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // RANDOMDISTRIBUTORMODELWIDGET_H
