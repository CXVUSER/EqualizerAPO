/********************************************************************************
** Form generated from reading UI file 'BiQuadFilterGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIQUADFILTERGUI_H
#define UI_BIQUADFILTERGUI_H

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

class Ui_BiQuadFilterGUI
{
public:
    QGridLayout *gridLayout;
    QDial *freqDial;
    QDial *qDial;
    QDoubleSpinBox *freqSpinBox;
    QSpacerItem *horizontalSpacer;
    QDial *gainDial;
    QDoubleSpinBox *gainSpinBox;
    QDoubleSpinBox *qSpinBox;
    QLabel *gainLabel;
    QComboBox *qComboBox;
    QComboBox *freqComboBox;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *typeComboBox;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *BiQuadFilterGUI)
    {
        if (BiQuadFilterGUI->objectName().isEmpty())
            BiQuadFilterGUI->setObjectName(QString::fromUtf8("BiQuadFilterGUI"));
        BiQuadFilterGUI->resize(734, 66);
        BiQuadFilterGUI->setWindowTitle(QString::fromUtf8(""));
        gridLayout = new QGridLayout(BiQuadFilterGUI);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        freqDial = new QDial(BiQuadFilterGUI);
        freqDial->setObjectName(QString::fromUtf8("freqDial"));
        freqDial->setMinimumSize(QSize(0, 66));
        freqDial->setMaximumSize(QSize(16777215, 66));
        freqDial->setMaximum(1000);
        freqDial->setPageStep(10);
        freqDial->setValue(566);

        gridLayout->addWidget(freqDial, 0, 2, 2, 1);

        qDial = new QDial(BiQuadFilterGUI);
        qDial->setObjectName(QString::fromUtf8("qDial"));
        qDial->setMinimumSize(QSize(0, 66));
        qDial->setMaximumSize(QSize(16777215, 66));
        qDial->setMinimum(0);
        qDial->setMaximum(1000);
        qDial->setNotchesVisible(false);

        gridLayout->addWidget(qDial, 0, 8, 2, 1);

        freqSpinBox = new QDoubleSpinBox(BiQuadFilterGUI);
        freqSpinBox->setObjectName(QString::fromUtf8("freqSpinBox"));
        freqSpinBox->setProperty("showGroupSeparator", QVariant(true));
        freqSpinBox->setMinimum(0.010000000000000);
        freqSpinBox->setMaximum(99999.990000000005239);
        freqSpinBox->setValue(1000.000000000000000);

        gridLayout->addWidget(freqSpinBox, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 4, 1, 1);

        gainDial = new QDial(BiQuadFilterGUI);
        gainDial->setObjectName(QString::fromUtf8("gainDial"));
        gainDial->setMinimumSize(QSize(0, 66));
        gainDial->setMaximumSize(QSize(16777215, 66));
        gainDial->setMinimum(-200);
        gainDial->setMaximum(200);
        gainDial->setPageStep(20);
        gainDial->setNotchTarget(9.850000000000000);
        gainDial->setNotchesVisible(true);

        gridLayout->addWidget(gainDial, 0, 5, 2, 1);

        gainSpinBox = new QDoubleSpinBox(BiQuadFilterGUI);
        gainSpinBox->setObjectName(QString::fromUtf8("gainSpinBox"));
        gainSpinBox->setMinimum(-199.990000000000009);
        gainSpinBox->setMaximum(199.990000000000009);

        gridLayout->addWidget(gainSpinBox, 1, 6, 1, 1);

        qSpinBox = new QDoubleSpinBox(BiQuadFilterGUI);
        qSpinBox->setObjectName(QString::fromUtf8("qSpinBox"));
        qSpinBox->setDecimals(4);
        qSpinBox->setMinimum(0.000100000000000);
        qSpinBox->setMaximum(999.999900000000025);
        qSpinBox->setSingleStep(0.100000000000000);
        qSpinBox->setValue(1.000000000000000);

        gridLayout->addWidget(qSpinBox, 1, 9, 1, 1);

        gainLabel = new QLabel(BiQuadFilterGUI);
        gainLabel->setObjectName(QString::fromUtf8("gainLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gainLabel->sizePolicy().hasHeightForWidth());
        gainLabel->setSizePolicy(sizePolicy);

        gridLayout->addWidget(gainLabel, 0, 6, 1, 1);

        qComboBox = new QComboBox(BiQuadFilterGUI);
        qComboBox->setObjectName(QString::fromUtf8("qComboBox"));

        gridLayout->addWidget(qComboBox, 0, 9, 1, 1);

        freqComboBox = new QComboBox(BiQuadFilterGUI);
        freqComboBox->setObjectName(QString::fromUtf8("freqComboBox"));

        gridLayout->addWidget(freqComboBox, 0, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 7, 1, 1);

        typeComboBox = new QComboBox(BiQuadFilterGUI);
        typeComboBox->setObjectName(QString::fromUtf8("typeComboBox"));

        gridLayout->addWidget(typeComboBox, 0, 0, 2, 1);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 1, 1, 1);


        retranslateUi(BiQuadFilterGUI);

        QMetaObject::connectSlotsByName(BiQuadFilterGUI);
    } // setupUi

    void retranslateUi(QWidget *BiQuadFilterGUI)
    {
        freqSpinBox->setSuffix(QCoreApplication::translate("BiQuadFilterGUI", " Hz", nullptr));
        gainSpinBox->setSuffix(QCoreApplication::translate("BiQuadFilterGUI", " dB", nullptr));
        gainLabel->setText(QCoreApplication::translate("BiQuadFilterGUI", "Gain:", nullptr));
        (void)BiQuadFilterGUI;
    } // retranslateUi

};

namespace Ui {
    class BiQuadFilterGUI: public Ui_BiQuadFilterGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIQUADFILTERGUI_H
