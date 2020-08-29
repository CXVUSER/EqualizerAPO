/********************************************************************************
** Form generated from reading UI file 'IncludeFilterGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INCLUDEFILTERGUI_H
#define UI_INCLUDEFILTERGUI_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "Editor/widgets/ResizingLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_IncludeFilterGUI
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *openFileToolButton;
    ResizingLineEdit *pathLineEdit;
    QToolButton *selectFileToolButton;
    QLabel *includeLabel;
    QLabel *errorLabel;

    void setupUi(QWidget *IncludeFilterGUI)
    {
        if (IncludeFilterGUI->objectName().isEmpty())
            IncludeFilterGUI->setObjectName(QString::fromUtf8("IncludeFilterGUI"));
        IncludeFilterGUI->resize(400, 26);
        IncludeFilterGUI->setWindowTitle(QString::fromUtf8(""));
        gridLayout = new QGridLayout(IncludeFilterGUI);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 5, 1, 1);

        openFileToolButton = new QToolButton(IncludeFilterGUI);
        openFileToolButton->setObjectName(QString::fromUtf8("openFileToolButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/go-up.ico"), QSize(), QIcon::Normal, QIcon::Off);
        openFileToolButton->setIcon(icon);

        gridLayout->addWidget(openFileToolButton, 0, 3, 1, 1);

        pathLineEdit = new ResizingLineEdit(IncludeFilterGUI);
        pathLineEdit->setObjectName(QString::fromUtf8("pathLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pathLineEdit->sizePolicy().hasHeightForWidth());
        pathLineEdit->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pathLineEdit, 0, 1, 1, 1);

        selectFileToolButton = new QToolButton(IncludeFilterGUI);
        selectFileToolButton->setObjectName(QString::fromUtf8("selectFileToolButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/document-open.ico"), QSize(), QIcon::Normal, QIcon::Off);
        selectFileToolButton->setIcon(icon1);

        gridLayout->addWidget(selectFileToolButton, 0, 2, 1, 1);

        includeLabel = new QLabel(IncludeFilterGUI);
        includeLabel->setObjectName(QString::fromUtf8("includeLabel"));

        gridLayout->addWidget(includeLabel, 0, 0, 1, 1);

        errorLabel = new QLabel(IncludeFilterGUI);
        errorLabel->setObjectName(QString::fromUtf8("errorLabel"));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        errorLabel->setPalette(palette);
        errorLabel->setText(QString::fromUtf8(""));

        gridLayout->addWidget(errorLabel, 0, 4, 1, 1);

        gridLayout->setColumnStretch(3, 1);

        retranslateUi(IncludeFilterGUI);

        QMetaObject::connectSlotsByName(IncludeFilterGUI);
    } // setupUi

    void retranslateUi(QWidget *IncludeFilterGUI)
    {
        openFileToolButton->setText(QCoreApplication::translate("IncludeFilterGUI", "Open file in editor", nullptr));
        selectFileToolButton->setText(QCoreApplication::translate("IncludeFilterGUI", "Select file", nullptr));
        includeLabel->setText(QCoreApplication::translate("IncludeFilterGUI", "Include:", nullptr));
        (void)IncludeFilterGUI;
    } // retranslateUi

};

namespace Ui {
    class IncludeFilterGUI: public Ui_IncludeFilterGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INCLUDEFILTERGUI_H
