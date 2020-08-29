/********************************************************************************
** Form generated from reading UI file 'CopyFilterGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYFILTERGUI_H
#define UI_COPYFILTERGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "CopyFilterGUIForm.h"

QT_BEGIN_NAMESPACE

class Ui_CopyFilterGUI
{
public:
    QGridLayout *gridLayout;
    QLabel *copyLabel;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_3;
    QScrollArea *scrollArea;
    CopyFilterGUIForm *form;
    QLabel *spaceReserveLabel;

    void setupUi(QWidget *CopyFilterGUI)
    {
        if (CopyFilterGUI->objectName().isEmpty())
            CopyFilterGUI->setObjectName(QString::fromUtf8("CopyFilterGUI"));
        CopyFilterGUI->resize(488, 94);
        CopyFilterGUI->setWindowTitle(QString::fromUtf8(""));
        gridLayout = new QGridLayout(CopyFilterGUI);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        copyLabel = new QLabel(CopyFilterGUI);
        copyLabel->setObjectName(QString::fromUtf8("copyLabel"));

        gridLayout->addWidget(copyLabel, 0, 0, 1, 1);

        tabWidget = new QTabWidget(CopyFilterGUI);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::East);
        tabWidget->setElideMode(Qt::ElideRight);
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setDocumentMode(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QGraphicsView(tab);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setFrameShape(QFrame::NoFrame);
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        graphicsView->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
        graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

        horizontalLayout->addWidget(graphicsView);

        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/applications-graphics-rotated.ico"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab, icon, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_3 = new QHBoxLayout(tab_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(tab_2);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        form = new CopyFilterGUIForm();
        form->setObjectName(QString::fromUtf8("form"));
        form->setGeometry(QRect(0, 0, 380, 90));
        scrollArea->setWidget(form);

        horizontalLayout_3->addWidget(scrollArea);

        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/format-justify-fill-rotated.ico"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_2, icon1, QString());

        gridLayout->addWidget(tabWidget, 0, 2, 1, 1);

        spaceReserveLabel = new QLabel(CopyFilterGUI);
        spaceReserveLabel->setObjectName(QString::fromUtf8("spaceReserveLabel"));
        spaceReserveLabel->setMaximumSize(QSize(16777215, 0));

        gridLayout->addWidget(spaceReserveLabel, 1, 0, 1, 1);


        retranslateUi(CopyFilterGUI);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CopyFilterGUI);
    } // setupUi

    void retranslateUi(QWidget *CopyFilterGUI)
    {
        copyLabel->setText(QCoreApplication::translate("CopyFilterGUI", "Copy channels:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QString());
#if QT_CONFIG(tooltip)
        tabWidget->setTabToolTip(tabWidget->indexOf(tab), QCoreApplication::translate("CopyFilterGUI", "Graph", nullptr));
#endif // QT_CONFIG(tooltip)
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QString());
#if QT_CONFIG(tooltip)
        tabWidget->setTabToolTip(tabWidget->indexOf(tab_2), QCoreApplication::translate("CopyFilterGUI", "Assignments", nullptr));
#endif // QT_CONFIG(tooltip)
        spaceReserveLabel->setText(QCoreApplication::translate("CopyFilterGUI", "Selected channels:", nullptr));
        (void)CopyFilterGUI;
    } // retranslateUi

};

namespace Ui {
    class CopyFilterGUI: public Ui_CopyFilterGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYFILTERGUI_H
