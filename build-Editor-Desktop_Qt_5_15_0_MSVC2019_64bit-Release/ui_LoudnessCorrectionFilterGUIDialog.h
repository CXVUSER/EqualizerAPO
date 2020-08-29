/********************************************************************************
** Form generated from reading UI file 'LoudnessCorrectionFilterGUIDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOUDNESSCORRECTIONFILTERGUIDIALOG_H
#define UI_LOUDNESSCORRECTIONFILTERGUIDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoudnessCorrectionFilterGUIDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *channelGroupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *leftRadioButton;
    QRadioButton *rightRadioButton;
    QRadioButton *bothRadioButton;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *stopButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *playButton;
    QLabel *label2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *levelLabel;
    QSpinBox *levelSpinBox;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label3;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *LoudnessCorrectionFilterGUIDialog)
    {
        if (LoudnessCorrectionFilterGUIDialog->objectName().isEmpty())
            LoudnessCorrectionFilterGUIDialog->setObjectName(QString::fromUtf8("LoudnessCorrectionFilterGUIDialog"));
        LoudnessCorrectionFilterGUIDialog->resize(486, 495);
        verticalLayout = new QVBoxLayout(LoudnessCorrectionFilterGUIDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(LoudnessCorrectionFilterGUIDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setTextFormat(Qt::RichText);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, -1);
        channelGroupBox = new QGroupBox(LoudnessCorrectionFilterGUIDialog);
        channelGroupBox->setObjectName(QString::fromUtf8("channelGroupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(channelGroupBox->sizePolicy().hasHeightForWidth());
        channelGroupBox->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(channelGroupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        leftRadioButton = new QRadioButton(channelGroupBox);
        leftRadioButton->setObjectName(QString::fromUtf8("leftRadioButton"));
        leftRadioButton->setChecked(true);

        horizontalLayout->addWidget(leftRadioButton);

        rightRadioButton = new QRadioButton(channelGroupBox);
        rightRadioButton->setObjectName(QString::fromUtf8("rightRadioButton"));

        horizontalLayout->addWidget(rightRadioButton);

        bothRadioButton = new QRadioButton(channelGroupBox);
        bothRadioButton->setObjectName(QString::fromUtf8("bothRadioButton"));

        horizontalLayout->addWidget(bothRadioButton);


        horizontalLayout_3->addWidget(channelGroupBox);


        verticalLayout->addLayout(horizontalLayout_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 4, 1, 1);

        stopButton = new QPushButton(LoudnessCorrectionFilterGUIDialog);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stopButton->sizePolicy().hasHeightForWidth());
        stopButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(stopButton, 1, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        playButton = new QPushButton(LoudnessCorrectionFilterGUIDialog);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        sizePolicy1.setHeightForWidth(playButton->sizePolicy().hasHeightForWidth());
        playButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(playButton, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        label2 = new QLabel(LoudnessCorrectionFilterGUIDialog);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setTextFormat(Qt::RichText);
        label2->setWordWrap(true);

        verticalLayout->addWidget(label2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        levelLabel = new QLabel(LoudnessCorrectionFilterGUIDialog);
        levelLabel->setObjectName(QString::fromUtf8("levelLabel"));

        horizontalLayout_2->addWidget(levelLabel);

        levelSpinBox = new QSpinBox(LoudnessCorrectionFilterGUIDialog);
        levelSpinBox->setObjectName(QString::fromUtf8("levelSpinBox"));
        sizePolicy1.setHeightForWidth(levelSpinBox->sizePolicy().hasHeightForWidth());
        levelSpinBox->setSizePolicy(sizePolicy1);
        levelSpinBox->setValue(75);

        horizontalLayout_2->addWidget(levelSpinBox);

        horizontalSpacer_2 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        label3 = new QLabel(LoudnessCorrectionFilterGUIDialog);
        label3->setObjectName(QString::fromUtf8("label3"));
        label3->setTextFormat(Qt::RichText);
        label3->setWordWrap(true);

        verticalLayout->addWidget(label3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(LoudnessCorrectionFilterGUIDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(LoudnessCorrectionFilterGUIDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), LoudnessCorrectionFilterGUIDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), LoudnessCorrectionFilterGUIDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(LoudnessCorrectionFilterGUIDialog);
    } // setupUi

    void retranslateUi(QDialog *LoudnessCorrectionFilterGUIDialog)
    {
        LoudnessCorrectionFilterGUIDialog->setWindowTitle(QCoreApplication::translate("LoudnessCorrectionFilterGUIDialog", "Calibration", nullptr));
        label->setText(QCoreApplication::translate("LoudnessCorrectionFilterGUIDialog", "<html><head/><body><p>For a correct calibration, a sound level meter is required.<br/>These are the steps for calibration of a stereo system:</p><ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Disable loudness correction during measurement<br/>(done automatically while this dialog is open)</li><li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Enable only one speaker (e.g. select left or right channel below)</li><li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Play pink noise at full application volume:</li></ul></body></html>", nullptr));
        channelGroupBox->setTitle(QCoreApplication::translate("LoudnessCorrectionFilterGUIDialog", "Channel", nullptr));
        leftRadioButton->setText(QCoreApplication::translate("LoudnessCorrectionFilterGUIDialog", "Left", nullptr));
        rightRadioButton->setText(QCoreApplication::translate("LoudnessCorrectionFilterGUIDialog", "Right", nullptr));
        bothRadioButton->setText(QCoreApplication::translate("LoudnessCorrectionFilterGUIDialog", "Both", nullptr));
        stopButton->setText(QCoreApplication::translate("LoudnessCorrectionFilterGUIDialog", "Stop", nullptr));
        playButton->setText(QCoreApplication::translate("LoudnessCorrectionFilterGUIDialog", "Play", nullptr));
        label2->setText(QCoreApplication::translate("LoudnessCorrectionFilterGUIDialog", "<html><head/><body><ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Adjust volume via Windows volume control or external volume control (amplifier, etc.) so that the sound level meter shows 75 dB at listening position. If that volume can not be reached, please adjust the following setting:</li></ul></body></html>", nullptr));
        levelLabel->setText(QCoreApplication::translate("LoudnessCorrectionFilterGUIDialog", "Level at listening position:", nullptr));
        levelSpinBox->setSuffix(QCoreApplication::translate("LoudnessCorrectionFilterGUIDialog", " dB", nullptr));
        levelSpinBox->setPrefix(QString());
        label3->setText(QCoreApplication::translate("LoudnessCorrectionFilterGUIDialog", "<html><head/><body><ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">The reference level will be set to the Windows volume for which the level at the listening position is 75 dB.</li><li style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">After calibration, volume should only be adjusted via Windows volume control</li></ul></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoudnessCorrectionFilterGUIDialog: public Ui_LoudnessCorrectionFilterGUIDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOUDNESSCORRECTIONFILTERGUIDIALOG_H
