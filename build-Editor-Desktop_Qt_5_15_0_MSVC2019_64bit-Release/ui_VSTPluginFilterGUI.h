/********************************************************************************
** Form generated from reading UI file 'VSTPluginFilterGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VSTPLUGINFILTERGUI_H
#define UI_VSTPLUGINFILTERGUI_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "Editor/widgets/ResizingLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_VSTPluginFilterGUI
{
public:
    QAction *embedAction;
    QGridLayout *gridLayout_3;
    ResizingLineEdit *pathLineEdit;
    QPushButton *openPanelButton;
    QLabel *label;
    QLabel *statusLabel;
    QSpacerItem *horizontalSpacer;
    QToolButton *optionsButton;
    QToolButton *selectButton;
    QFrame *frame;
    QPlainTextEdit *warningTextEdit;

    void setupUi(QWidget *VSTPluginFilterGUI)
    {
        if (VSTPluginFilterGUI->objectName().isEmpty())
            VSTPluginFilterGUI->setObjectName(QString::fromUtf8("VSTPluginFilterGUI"));
        VSTPluginFilterGUI->resize(542, 166);
        VSTPluginFilterGUI->setWindowTitle(QString::fromUtf8(""));
        embedAction = new QAction(VSTPluginFilterGUI);
        embedAction->setObjectName(QString::fromUtf8("embedAction"));
        embedAction->setCheckable(true);
        gridLayout_3 = new QGridLayout(VSTPluginFilterGUI);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setVerticalSpacing(5);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        pathLineEdit = new ResizingLineEdit(VSTPluginFilterGUI);
        pathLineEdit->setObjectName(QString::fromUtf8("pathLineEdit"));

        gridLayout_3->addWidget(pathLineEdit, 0, 1, 1, 1);

        openPanelButton = new QPushButton(VSTPluginFilterGUI);
        openPanelButton->setObjectName(QString::fromUtf8("openPanelButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openPanelButton->sizePolicy().hasHeightForWidth());
        openPanelButton->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(openPanelButton, 1, 2, 1, 2);

        label = new QLabel(VSTPluginFilterGUI);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        statusLabel = new QLabel(VSTPluginFilterGUI);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setText(QString::fromUtf8(""));

        gridLayout_3->addWidget(statusLabel, 1, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 4, 1, 1);

        optionsButton = new QToolButton(VSTPluginFilterGUI);
        optionsButton->setObjectName(QString::fromUtf8("optionsButton"));
        optionsButton->setPopupMode(QToolButton::MenuButtonPopup);
        optionsButton->setToolButtonStyle(Qt::ToolButtonTextOnly);

        gridLayout_3->addWidget(optionsButton, 0, 3, 1, 1);

        selectButton = new QToolButton(VSTPluginFilterGUI);
        selectButton->setObjectName(QString::fromUtf8("selectButton"));
        selectButton->setText(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/document-open.ico"), QSize(), QIcon::Normal, QIcon::Off);
        selectButton->setIcon(icon);

        gridLayout_3->addWidget(selectButton, 0, 2, 1, 1);

        frame = new QFrame(VSTPluginFilterGUI);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        gridLayout_3->addWidget(frame, 2, 0, 1, 4);

        warningTextEdit = new QPlainTextEdit(VSTPluginFilterGUI);
        warningTextEdit->setObjectName(QString::fromUtf8("warningTextEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(warningTextEdit->sizePolicy().hasHeightForWidth());
        warningTextEdit->setSizePolicy(sizePolicy2);
        QPalette palette;
        QBrush brush(QColor(255, 255, 127, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        warningTextEdit->setPalette(palette);
        warningTextEdit->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout_3->addWidget(warningTextEdit, 3, 0, 1, 4);

        gridLayout_3->setColumnStretch(4, 1);

        retranslateUi(VSTPluginFilterGUI);
        QObject::connect(optionsButton, SIGNAL(clicked()), optionsButton, SLOT(showMenu()));

        QMetaObject::connectSlotsByName(VSTPluginFilterGUI);
    } // setupUi

    void retranslateUi(QWidget *VSTPluginFilterGUI)
    {
        embedAction->setText(QCoreApplication::translate("VSTPluginFilterGUI", "Embed", nullptr));
        openPanelButton->setText(QCoreApplication::translate("VSTPluginFilterGUI", "Open panel", nullptr));
        label->setText(QCoreApplication::translate("VSTPluginFilterGUI", "VST plugin:", nullptr));
        optionsButton->setText(QCoreApplication::translate("VSTPluginFilterGUI", "Options", nullptr));
        (void)VSTPluginFilterGUI;
    } // retranslateUi

};

namespace Ui {
    class VSTPluginFilterGUI: public Ui_VSTPluginFilterGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VSTPLUGINFILTERGUI_H
