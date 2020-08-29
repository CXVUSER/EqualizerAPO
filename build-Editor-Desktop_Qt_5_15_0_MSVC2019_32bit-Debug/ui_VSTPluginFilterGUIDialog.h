/********************************************************************************
** Form generated from reading UI file 'VSTPluginFilterGUIDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VSTPLUGINFILTERGUIDIALOG_H
#define UI_VSTPLUGINFILTERGUIDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>

QT_BEGIN_NAMESPACE

class Ui_VSTPluginFilterGUIDialog
{
public:
    QGridLayout *gridLayout;
    QCheckBox *autoApplyCheckBox;
    QDialogButtonBox *buttonBox;
    QFrame *frame;

    void setupUi(QDialog *VSTPluginFilterGUIDialog)
    {
        if (VSTPluginFilterGUIDialog->objectName().isEmpty())
            VSTPluginFilterGUIDialog->setObjectName(QString::fromUtf8("VSTPluginFilterGUIDialog"));
        VSTPluginFilterGUIDialog->resize(459, 300);
        VSTPluginFilterGUIDialog->setWindowTitle(QString::fromUtf8(""));
        gridLayout = new QGridLayout(VSTPluginFilterGUIDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        autoApplyCheckBox = new QCheckBox(VSTPluginFilterGUIDialog);
        autoApplyCheckBox->setObjectName(QString::fromUtf8("autoApplyCheckBox"));

        gridLayout->addWidget(autoApplyCheckBox, 1, 1, 1, 1);

        buttonBox = new QDialogButtonBox(VSTPluginFilterGUIDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

        frame = new QFrame(VSTPluginFilterGUIDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frame, 0, 0, 1, 2);


        retranslateUi(VSTPluginFilterGUIDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), VSTPluginFilterGUIDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), VSTPluginFilterGUIDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(VSTPluginFilterGUIDialog);
    } // setupUi

    void retranslateUi(QDialog *VSTPluginFilterGUIDialog)
    {
        autoApplyCheckBox->setText(QCoreApplication::translate("VSTPluginFilterGUIDialog", "Apply automatically", nullptr));
        (void)VSTPluginFilterGUIDialog;
    } // retranslateUi

};

namespace Ui {
    class VSTPluginFilterGUIDialog: public Ui_VSTPluginFilterGUIDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VSTPLUGINFILTERGUIDIALOG_H
