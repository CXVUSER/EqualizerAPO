/********************************************************************************
** Form generated from reading UI file 'DelayFilterGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELAYFILTERGUI_H
#define UI_DELAYFILTERGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DelayFilterGUI
{
public:
    QGridLayout *gridLayout;
    QDoubleSpinBox *delaySpinBox;
    QLabel *delayLabel;
    QDial *delayDial;
    QComboBox *unitComboBox;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *DelayFilterGUI)
    {
        if (DelayFilterGUI->objectName().isEmpty())
            DelayFilterGUI->setObjectName(QString::fromUtf8("DelayFilterGUI"));
        DelayFilterGUI->resize(262, 66);
        DelayFilterGUI->setWindowTitle(QString::fromUtf8(""));
        gridLayout = new QGridLayout(DelayFilterGUI);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        delaySpinBox = new QDoubleSpinBox(DelayFilterGUI);
        delaySpinBox->setObjectName(QString::fromUtf8("delaySpinBox"));
        delaySpinBox->setMaximum(1000000.000000000000000);

        gridLayout->addWidget(delaySpinBox, 1, 2, 1, 1);

        delayLabel = new QLabel(DelayFilterGUI);
        delayLabel->setObjectName(QString::fromUtf8("delayLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(delayLabel->sizePolicy().hasHeightForWidth());
        delayLabel->setSizePolicy(sizePolicy);

        gridLayout->addWidget(delayLabel, 0, 0, 2, 1);

        delayDial = new QDial(DelayFilterGUI);
        delayDial->setObjectName(QString::fromUtf8("delayDial"));
        delayDial->setMinimumSize(QSize(0, 66));
        delayDial->setMaximum(1000);

        gridLayout->addWidget(delayDial, 0, 1, 2, 1);

        unitComboBox = new QComboBox(DelayFilterGUI);
        unitComboBox->addItem(QString());
        unitComboBox->addItem(QString());
        unitComboBox->setObjectName(QString::fromUtf8("unitComboBox"));

        gridLayout->addWidget(unitComboBox, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 2, 1);

        gridLayout->setColumnStretch(3, 1);

        retranslateUi(DelayFilterGUI);

        QMetaObject::connectSlotsByName(DelayFilterGUI);
    } // setupUi

    void retranslateUi(QWidget *DelayFilterGUI)
    {
        delaySpinBox->setSuffix(QCoreApplication::translate("DelayFilterGUI", " ms", nullptr));
        delayLabel->setText(QCoreApplication::translate("DelayFilterGUI", "Delay:", nullptr));
        unitComboBox->setItemText(0, QCoreApplication::translate("DelayFilterGUI", "Time", nullptr));
        unitComboBox->setItemText(1, QCoreApplication::translate("DelayFilterGUI", "Samples", nullptr));

        (void)DelayFilterGUI;
    } // retranslateUi

};

namespace Ui {
    class DelayFilterGUI: public Ui_DelayFilterGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELAYFILTERGUI_H
