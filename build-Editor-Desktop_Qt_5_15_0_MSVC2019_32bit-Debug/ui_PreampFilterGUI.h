/********************************************************************************
** Form generated from reading UI file 'PreampFilterGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREAMPFILTERGUI_H
#define UI_PREAMPFILTERGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreampFilterGUI
{
public:
    QGridLayout *gridLayout;
    QLabel *gainLabel;
    QDoubleSpinBox *doubleSpinBox;
    QDial *dial;
    QSpacerItem *horizontalSpacer;
    QLabel *label;

    void setupUi(QWidget *PreampFilterGUI)
    {
        if (PreampFilterGUI->objectName().isEmpty())
            PreampFilterGUI->setObjectName(QString::fromUtf8("PreampFilterGUI"));
        PreampFilterGUI->resize(525, 66);
        PreampFilterGUI->setWindowTitle(QString::fromUtf8(""));
        gridLayout = new QGridLayout(PreampFilterGUI);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gainLabel = new QLabel(PreampFilterGUI);
        gainLabel->setObjectName(QString::fromUtf8("gainLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gainLabel->sizePolicy().hasHeightForWidth());
        gainLabel->setSizePolicy(sizePolicy);

        gridLayout->addWidget(gainLabel, 0, 4, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(PreampFilterGUI);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(doubleSpinBox->sizePolicy().hasHeightForWidth());
        doubleSpinBox->setSizePolicy(sizePolicy1);
        doubleSpinBox->setAccelerated(true);
        doubleSpinBox->setMinimum(-100.000000000000000);
        doubleSpinBox->setMaximum(100.000000000000000);
        doubleSpinBox->setSingleStep(0.100000000000000);

        gridLayout->addWidget(doubleSpinBox, 1, 4, 1, 1);

        dial = new QDial(PreampFilterGUI);
        dial->setObjectName(QString::fromUtf8("dial"));
        sizePolicy.setHeightForWidth(dial->sizePolicy().hasHeightForWidth());
        dial->setSizePolicy(sizePolicy);
        dial->setMinimumSize(QSize(0, 66));
        dial->setMaximumSize(QSize(16777215, 66));
        dial->setMinimum(-200);
        dial->setMaximum(200);
        dial->setPageStep(20);
        dial->setOrientation(Qt::Vertical);
        dial->setNotchTarget(9.850000000000000);
        dial->setNotchesVisible(true);

        gridLayout->addWidget(dial, 0, 2, 2, 1);

        horizontalSpacer = new QSpacerItem(229, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 5, 2, 1);

        label = new QLabel(PreampFilterGUI);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 2, 1);


        retranslateUi(PreampFilterGUI);

        QMetaObject::connectSlotsByName(PreampFilterGUI);
    } // setupUi

    void retranslateUi(QWidget *PreampFilterGUI)
    {
        gainLabel->setText(QCoreApplication::translate("PreampFilterGUI", "Gain:", nullptr));
        doubleSpinBox->setSuffix(QCoreApplication::translate("PreampFilterGUI", " dB", nullptr));
        label->setText(QCoreApplication::translate("PreampFilterGUI", "Preamplification:", nullptr));
        (void)PreampFilterGUI;
    } // retranslateUi

};

namespace Ui {
    class PreampFilterGUI: public Ui_PreampFilterGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREAMPFILTERGUI_H
