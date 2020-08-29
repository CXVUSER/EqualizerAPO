/********************************************************************************
** Form generated from reading UI file 'LoudnessCorrectionFilterGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOUDNESSCORRECTIONFILTERGUI_H
#define UI_LOUDNESSCORRECTIONFILTERGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoudnessCorrectionFilterGUI
{
public:
    QGridLayout *gridLayout;
    QDoubleSpinBox *volumeSpinBox;
    QSpacerItem *horizontalSpacer_3;
    QLabel *refLevelLabel;
    QSpacerItem *horizontalSpacer_4;
    QLabel *volumeLabel;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_5;
    QDial *refOffsetDial;
    QLabel *attLabel;
    QSpacerItem *horizontalSpacer_2;
    QSpinBox *refLevelSpinBox;
    QDial *attDial;
    QDoubleSpinBox *attSpinBox;
    QSpinBox *refOffsetSpinBox;
    QLabel *refOffsetLabel;
    QSpacerItem *horizontalSpacer;
    QDial *refLevelDial;
    QLabel *label;
    QPushButton *calibrateButton;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *LoudnessCorrectionFilterGUI)
    {
        if (LoudnessCorrectionFilterGUI->objectName().isEmpty())
            LoudnessCorrectionFilterGUI->setObjectName(QString::fromUtf8("LoudnessCorrectionFilterGUI"));
        LoudnessCorrectionFilterGUI->resize(1048, 66);
        LoudnessCorrectionFilterGUI->setWindowTitle(QString::fromUtf8(""));
        gridLayout = new QGridLayout(LoudnessCorrectionFilterGUI);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        volumeSpinBox = new QDoubleSpinBox(LoudnessCorrectionFilterGUI);
        volumeSpinBox->setObjectName(QString::fromUtf8("volumeSpinBox"));
        volumeSpinBox->setEnabled(false);
        volumeSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        volumeSpinBox->setSuffix(QString::fromUtf8(" dB"));
        volumeSpinBox->setMinimum(-99.989999999999995);

        gridLayout->addWidget(volumeSpinBox, 1, 13, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 7, 1, 1);

        refLevelLabel = new QLabel(LoudnessCorrectionFilterGUI);
        refLevelLabel->setObjectName(QString::fromUtf8("refLevelLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(refLevelLabel->sizePolicy().hasHeightForWidth());
        refLevelLabel->setSizePolicy(sizePolicy);

        gridLayout->addWidget(refLevelLabel, 0, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 14, 1, 1);

        volumeLabel = new QLabel(LoudnessCorrectionFilterGUI);
        volumeLabel->setObjectName(QString::fromUtf8("volumeLabel"));

        gridLayout->addWidget(volumeLabel, 0, 13, 1, 1);

        label_2 = new QLabel(LoudnessCorrectionFilterGUI);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setPointSize(7);
        font.setBold(false);
        font.setItalic(true);
        font.setWeight(50);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 10, 1, 1);

        refOffsetDial = new QDial(LoudnessCorrectionFilterGUI);
        refOffsetDial->setObjectName(QString::fromUtf8("refOffsetDial"));
        refOffsetDial->setMinimumSize(QSize(0, 66));
        refOffsetDial->setMaximumSize(QSize(16777215, 66));
        refOffsetDial->setMinimum(-99);

        gridLayout->addWidget(refOffsetDial, 0, 5, 2, 1);

        attLabel = new QLabel(LoudnessCorrectionFilterGUI);
        attLabel->setObjectName(QString::fromUtf8("attLabel"));
        sizePolicy.setHeightForWidth(attLabel->sizePolicy().hasHeightForWidth());
        attLabel->setSizePolicy(sizePolicy);

        gridLayout->addWidget(attLabel, 0, 9, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 4, 1, 1);

        refLevelSpinBox = new QSpinBox(LoudnessCorrectionFilterGUI);
        refLevelSpinBox->setObjectName(QString::fromUtf8("refLevelSpinBox"));
        refLevelSpinBox->setSuffix(QString::fromUtf8(" dB"));
        refLevelSpinBox->setMinimum(-999);
        refLevelSpinBox->setMaximum(999);

        gridLayout->addWidget(refLevelSpinBox, 1, 3, 1, 1);

        attDial = new QDial(LoudnessCorrectionFilterGUI);
        attDial->setObjectName(QString::fromUtf8("attDial"));
        attDial->setMinimumSize(QSize(0, 66));
        attDial->setMaximumSize(QSize(16777215, 66));
        attDial->setMinimum(0);
        attDial->setMaximum(100);
        attDial->setValue(100);

        gridLayout->addWidget(attDial, 0, 8, 2, 1);

        attSpinBox = new QDoubleSpinBox(LoudnessCorrectionFilterGUI);
        attSpinBox->setObjectName(QString::fromUtf8("attSpinBox"));
        attSpinBox->setMaximum(1.000000000000000);
        attSpinBox->setSingleStep(0.010000000000000);
        attSpinBox->setValue(1.000000000000000);

        gridLayout->addWidget(attSpinBox, 1, 9, 1, 1);

        refOffsetSpinBox = new QSpinBox(LoudnessCorrectionFilterGUI);
        refOffsetSpinBox->setObjectName(QString::fromUtf8("refOffsetSpinBox"));
        refOffsetSpinBox->setSuffix(QString::fromUtf8(" dB"));
        refOffsetSpinBox->setMinimum(-999);
        refOffsetSpinBox->setMaximum(999);

        gridLayout->addWidget(refOffsetSpinBox, 1, 6, 1, 1);

        refOffsetLabel = new QLabel(LoudnessCorrectionFilterGUI);
        refOffsetLabel->setObjectName(QString::fromUtf8("refOffsetLabel"));
        sizePolicy.setHeightForWidth(refOffsetLabel->sizePolicy().hasHeightForWidth());
        refOffsetLabel->setSizePolicy(sizePolicy);

        gridLayout->addWidget(refOffsetLabel, 0, 6, 1, 1);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        refLevelDial = new QDial(LoudnessCorrectionFilterGUI);
        refLevelDial->setObjectName(QString::fromUtf8("refLevelDial"));
        refLevelDial->setMinimumSize(QSize(0, 66));
        refLevelDial->setMaximumSize(QSize(16777215, 66));
        refLevelDial->setMinimum(-99);

        gridLayout->addWidget(refLevelDial, 0, 2, 2, 1);

        label = new QLabel(LoudnessCorrectionFilterGUI);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        calibrateButton = new QPushButton(LoudnessCorrectionFilterGUI);
        calibrateButton->setObjectName(QString::fromUtf8("calibrateButton"));

        gridLayout->addWidget(calibrateButton, 0, 11, 2, 1);

        horizontalSpacer_6 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 0, 12, 1, 1);


        retranslateUi(LoudnessCorrectionFilterGUI);
        QObject::connect(refLevelDial, SIGNAL(valueChanged(int)), refLevelSpinBox, SLOT(setValue(int)));
        QObject::connect(refLevelSpinBox, SIGNAL(valueChanged(int)), refLevelDial, SLOT(setValue(int)));
        QObject::connect(refOffsetDial, SIGNAL(valueChanged(int)), refOffsetSpinBox, SLOT(setValue(int)));
        QObject::connect(refOffsetSpinBox, SIGNAL(valueChanged(int)), refOffsetDial, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(LoudnessCorrectionFilterGUI);
    } // setupUi

    void retranslateUi(QWidget *LoudnessCorrectionFilterGUI)
    {
        refLevelLabel->setText(QCoreApplication::translate("LoudnessCorrectionFilterGUI", "Reference level:", nullptr));
        volumeLabel->setText(QCoreApplication::translate("LoudnessCorrectionFilterGUI", "Master volume:", nullptr));
        label_2->setText(QCoreApplication::translate("LoudnessCorrectionFilterGUI", "contributed by\n"
"Alexander Walch", nullptr));
        attLabel->setText(QCoreApplication::translate("LoudnessCorrectionFilterGUI", "Attenuation:", nullptr));
        refOffsetLabel->setText(QCoreApplication::translate("LoudnessCorrectionFilterGUI", "Reference offset:", nullptr));
        label->setText(QCoreApplication::translate("LoudnessCorrectionFilterGUI", "Loudness correction:", nullptr));
        calibrateButton->setText(QCoreApplication::translate("LoudnessCorrectionFilterGUI", "Calibrate", nullptr));
        (void)LoudnessCorrectionFilterGUI;
    } // retranslateUi

};

namespace Ui {
    class LoudnessCorrectionFilterGUI: public Ui_LoudnessCorrectionFilterGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOUDNESSCORRECTIONFILTERGUI_H
