/********************************************************************************
** Form generated from reading UI file 'FilterTableRow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERTABLEROW_H
#define UI_FILTERTABLEROW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "Editor/widgets/CompactToolBar.h"
#include "Editor/widgets/EscapableLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_FilterTableRow
{
public:
    QAction *actionAdd;
    QAction *actionRemove;
    QAction *actionEditText;
    QHBoxLayout *horizontalLayout;
    QLabel *labelNumber;
    CompactToolBar *toolBar;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout;
    EscapableLineEdit *lineEdit;

    void setupUi(QWidget *FilterTableRow)
    {
        if (FilterTableRow->objectName().isEmpty())
            FilterTableRow->setObjectName(QString::fromUtf8("FilterTableRow"));
        FilterTableRow->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FilterTableRow->sizePolicy().hasHeightForWidth());
        FilterTableRow->setSizePolicy(sizePolicy);
        FilterTableRow->setWindowTitle(QString::fromUtf8("Form"));
        actionAdd = new QAction(FilterTableRow);
        actionAdd->setObjectName(QString::fromUtf8("actionAdd"));
        actionAdd->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/list-add-green.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionAdd->setIcon(icon);
        actionRemove = new QAction(FilterTableRow);
        actionRemove->setObjectName(QString::fromUtf8("actionRemove"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/list-remove-red.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionRemove->setIcon(icon1);
        actionEditText = new QAction(FilterTableRow);
        actionEditText->setObjectName(QString::fromUtf8("actionEditText"));
        actionEditText->setCheckable(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/accessories-text-editor.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionEditText->setIcon(icon2);
        horizontalLayout = new QHBoxLayout(FilterTableRow);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 1, 6, 0);
        labelNumber = new QLabel(FilterTableRow);
        labelNumber->setObjectName(QString::fromUtf8("labelNumber"));
        labelNumber->setMinimumSize(QSize(25, 0));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        labelNumber->setPalette(palette);
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        labelNumber->setFont(font);
        labelNumber->setCursor(QCursor(Qt::OpenHandCursor));
        labelNumber->setText(QString::fromUtf8("99"));
        labelNumber->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(labelNumber);

        toolBar = new CompactToolBar(FilterTableRow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toolBar->sizePolicy().hasHeightForWidth());
        toolBar->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(toolBar);

        stackedWidget = new QStackedWidget(FilterTableRow);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy2);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout = new QGridLayout(page);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new EscapableLineEdit(page);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 2, 1, 1);

        stackedWidget->addWidget(page);

        horizontalLayout->addWidget(stackedWidget);


        retranslateUi(FilterTableRow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FilterTableRow);
    } // setupUi

    void retranslateUi(QWidget *FilterTableRow)
    {
        actionAdd->setText(QCoreApplication::translate("FilterTableRow", "Add", nullptr));
        actionRemove->setText(QCoreApplication::translate("FilterTableRow", "Remove", nullptr));
        actionEditText->setText(QCoreApplication::translate("FilterTableRow", "Edit text", nullptr));
        (void)FilterTableRow;
    } // retranslateUi

};

namespace Ui {
    class FilterTableRow: public Ui_FilterTableRow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERTABLEROW_H
