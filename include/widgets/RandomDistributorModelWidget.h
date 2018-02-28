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

    void setupUi(QWidget *RandomDistributorModelWidget)
    {
        if (RandomDistributorModelWidget->objectName().isEmpty())
            RandomDistributorModelWidget->setObjectName(QStringLiteral("RandomDistributorModelWidget"));
        RandomDistributorModelWidget->resize(145, 64);
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

        formLayout->setWidget(1, QFormLayout::LabelRole, modeLabel);

        modeCheckBox = new QCheckBox(RandomDistributorModelWidget);
        modeCheckBox->setObjectName(QStringLiteral("modeCheckBox"));

        formLayout->setWidget(1, QFormLayout::FieldRole, modeCheckBox);


        retranslateUi(RandomDistributorModelWidget);

        QMetaObject::connectSlotsByName(RandomDistributorModelWidget);
    } // setupUi

    void retranslateUi(QWidget *RandomDistributorModelWidget)
    {
        RandomDistributorModelWidget->setWindowTitle(QApplication::translate("RandomDistributorModelWidget", "Form", Q_NULLPTR));
        countLabel->setText(QApplication::translate("RandomDistributorModelWidget", "Amount", Q_NULLPTR));
        modeLabel->setText(QApplication::translate("RandomDistributorModelWidget", "Mode", Q_NULLPTR));
        modeCheckBox->setText(QApplication::translate("RandomDistributorModelWidget", "GPU", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RandomDistributorModelWidget: public Ui_RandomDistributorModelWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // RANDOMDISTRIBUTORMODELWIDGET_H
