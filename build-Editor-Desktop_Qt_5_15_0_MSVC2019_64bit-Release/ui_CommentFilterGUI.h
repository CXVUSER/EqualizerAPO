/********************************************************************************
** Form generated from reading UI file 'CommentFilterGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMENTFILTERGUI_H
#define UI_COMMENTFILTERGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "Editor/widgets/CompactToolBar.h"

QT_BEGIN_NAMESPACE

class Ui_CommentFilterGUI
{
public:
    QAction *actionPowerOn;
    QHBoxLayout *horizontalLayout;
    CompactToolBar *toolBar;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *CommentFilterGUI)
    {
        if (CommentFilterGUI->objectName().isEmpty())
            CommentFilterGUI->setObjectName(QString::fromUtf8("CommentFilterGUI"));
        CommentFilterGUI->resize(400, 104);
        CommentFilterGUI->setWindowTitle(QString::fromUtf8(""));
        actionPowerOn = new QAction(CommentFilterGUI);
        actionPowerOn->setObjectName(QString::fromUtf8("actionPowerOn"));
        actionPowerOn->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/power_off.ico"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/icons/power_on.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionPowerOn->setIcon(icon);
        horizontalLayout = new QHBoxLayout(CommentFilterGUI);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        toolBar = new CompactToolBar(CommentFilterGUI);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));

        horizontalLayout->addWidget(toolBar);

        horizontalSpacer = new QSpacerItem(379, 37, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalLayout->setStretch(1, 1);

        retranslateUi(CommentFilterGUI);

        QMetaObject::connectSlotsByName(CommentFilterGUI);
    } // setupUi

    void retranslateUi(QWidget *CommentFilterGUI)
    {
        actionPowerOn->setText(QCoreApplication::translate("CommentFilterGUI", "Power on", nullptr));
        (void)CommentFilterGUI;
    } // retranslateUi

};

namespace Ui {
    class CommentFilterGUI: public Ui_CommentFilterGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMENTFILTERGUI_H
