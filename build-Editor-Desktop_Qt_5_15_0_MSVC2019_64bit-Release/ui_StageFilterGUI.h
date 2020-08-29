/********************************************************************************
** Form generated from reading UI file 'StageFilterGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STAGEFILTERGUI_H
#define UI_STAGEFILTERGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StageFilterGUI
{
public:
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QGroupBox *playbackGroupBox;
    QHBoxLayout *horizontalLayout;
    QCheckBox *preMixCheckBox;
    QCheckBox *postMixCheckBox;
    QGroupBox *captureGroupBox;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *captureCheckBox;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *StageFilterGUI)
    {
        if (StageFilterGUI->objectName().isEmpty())
            StageFilterGUI->setObjectName(QString::fromUtf8("StageFilterGUI"));
        StageFilterGUI->resize(639, 68);
        StageFilterGUI->setWindowTitle(QString::fromUtf8(""));
        horizontalLayout_3 = new QHBoxLayout(StageFilterGUI);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(StageFilterGUI);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        playbackGroupBox = new QGroupBox(StageFilterGUI);
        playbackGroupBox->setObjectName(QString::fromUtf8("playbackGroupBox"));
        horizontalLayout = new QHBoxLayout(playbackGroupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        preMixCheckBox = new QCheckBox(playbackGroupBox);
        preMixCheckBox->setObjectName(QString::fromUtf8("preMixCheckBox"));

        horizontalLayout->addWidget(preMixCheckBox);

        postMixCheckBox = new QCheckBox(playbackGroupBox);
        postMixCheckBox->setObjectName(QString::fromUtf8("postMixCheckBox"));

        horizontalLayout->addWidget(postMixCheckBox);


        horizontalLayout_3->addWidget(playbackGroupBox);

        captureGroupBox = new QGroupBox(StageFilterGUI);
        captureGroupBox->setObjectName(QString::fromUtf8("captureGroupBox"));
        horizontalLayout_2 = new QHBoxLayout(captureGroupBox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        captureCheckBox = new QCheckBox(captureGroupBox);
        captureCheckBox->setObjectName(QString::fromUtf8("captureCheckBox"));

        horizontalLayout_2->addWidget(captureCheckBox);


        horizontalLayout_3->addWidget(captureGroupBox);

        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        retranslateUi(StageFilterGUI);

        QMetaObject::connectSlotsByName(StageFilterGUI);
    } // setupUi

    void retranslateUi(QWidget *StageFilterGUI)
    {
        label->setText(QCoreApplication::translate("StageFilterGUI", "Selected processing stage:", nullptr));
        playbackGroupBox->setTitle(QCoreApplication::translate("StageFilterGUI", "Playback", nullptr));
        preMixCheckBox->setText(QCoreApplication::translate("StageFilterGUI", "Pre-mix", nullptr));
        postMixCheckBox->setText(QCoreApplication::translate("StageFilterGUI", "Post-mix", nullptr));
        captureGroupBox->setTitle(QCoreApplication::translate("StageFilterGUI", "Capture", nullptr));
        captureCheckBox->setText(QCoreApplication::translate("StageFilterGUI", "Capture", nullptr));
        (void)StageFilterGUI;
    } // retranslateUi

};

namespace Ui {
    class StageFilterGUI: public Ui_StageFilterGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STAGEFILTERGUI_H
