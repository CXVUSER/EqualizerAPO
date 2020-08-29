/********************************************************************************
** Form generated from reading UI file 'GraphicEQFilterGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICEQFILTERGUI_H
#define UI_GRAPHICEQFILTERGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "GraphicEQFilterGUIView.h"

QT_BEGIN_NAMESPACE

class Ui_GraphicEQFilterGUI
{
public:
    QAction *actionImport;
    QAction *actionExport;
    QAction *actionInvertResponse;
    QAction *actionNormalizeResponse;
    QAction *actionResetResponse;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QRadioButton *radioButton15;
    QRadioButton *radioButton31;
    QRadioButton *radioButtonVar;
    GraphicEQFilterGUIView *graphicsView;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidget;
    QToolBar *toolBar;

    void setupUi(QWidget *GraphicEQFilterGUI)
    {
        if (GraphicEQFilterGUI->objectName().isEmpty())
            GraphicEQFilterGUI->setObjectName(QString::fromUtf8("GraphicEQFilterGUI"));
        GraphicEQFilterGUI->resize(623, 124);
        GraphicEQFilterGUI->setWindowTitle(QString::fromUtf8(""));
        actionImport = new QAction(GraphicEQFilterGUI);
        actionImport->setObjectName(QString::fromUtf8("actionImport"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/document-open.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionImport->setIcon(icon);
        actionExport = new QAction(GraphicEQFilterGUI);
        actionExport->setObjectName(QString::fromUtf8("actionExport"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/document-save-as.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionExport->setIcon(icon1);
        actionInvertResponse = new QAction(GraphicEQFilterGUI);
        actionInvertResponse->setObjectName(QString::fromUtf8("actionInvertResponse"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/invert_response.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionInvertResponse->setIcon(icon2);
        actionNormalizeResponse = new QAction(GraphicEQFilterGUI);
        actionNormalizeResponse->setObjectName(QString::fromUtf8("actionNormalizeResponse"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/normalize_response.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionNormalizeResponse->setIcon(icon3);
        actionResetResponse = new QAction(GraphicEQFilterGUI);
        actionResetResponse->setObjectName(QString::fromUtf8("actionResetResponse"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/reset_response.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionResetResponse->setIcon(icon4);
        horizontalLayout = new QHBoxLayout(GraphicEQFilterGUI);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(GraphicEQFilterGUI);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label);

        radioButton15 = new QRadioButton(GraphicEQFilterGUI);
        radioButton15->setObjectName(QString::fromUtf8("radioButton15"));

        verticalLayout->addWidget(radioButton15);

        radioButton31 = new QRadioButton(GraphicEQFilterGUI);
        radioButton31->setObjectName(QString::fromUtf8("radioButton31"));

        verticalLayout->addWidget(radioButton31);

        radioButtonVar = new QRadioButton(GraphicEQFilterGUI);
        radioButtonVar->setObjectName(QString::fromUtf8("radioButtonVar"));
        radioButtonVar->setChecked(true);

        verticalLayout->addWidget(radioButtonVar);


        horizontalLayout->addLayout(verticalLayout);

        graphicsView = new GraphicEQFilterGUIView(GraphicEQFilterGUI);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        graphicsView->setMinimumSize(QSize(0, 100));
        graphicsView->setMouseTracking(true);
        graphicsView->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
        graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

        horizontalLayout->addWidget(graphicsView);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableWidget = new QTableWidget(GraphicEQFilterGUI);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        tableWidget->setMinimumSize(QSize(50, 0));
        QPalette palette;
        QBrush brush(QColor(51, 153, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush);
        QBrush brush1(QColor(122, 189, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush);
        tableWidget->setPalette(palette);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->setWordWrap(false);
        tableWidget->setColumnCount(2);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setMinimumSectionSize(10);
        tableWidget->horizontalHeader()->setDefaultSectionSize(10);
        tableWidget->horizontalHeader()->setHighlightSections(false);
        tableWidget->verticalHeader()->setMinimumSectionSize(23);
        tableWidget->verticalHeader()->setDefaultSectionSize(20);

        verticalLayout_2->addWidget(tableWidget);

        toolBar = new QToolBar(GraphicEQFilterGUI);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));

        verticalLayout_2->addWidget(toolBar);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(1, 1);

        retranslateUi(GraphicEQFilterGUI);

        QMetaObject::connectSlotsByName(GraphicEQFilterGUI);
    } // setupUi

    void retranslateUi(QWidget *GraphicEQFilterGUI)
    {
        actionImport->setText(QCoreApplication::translate("GraphicEQFilterGUI", "Import", nullptr));
        actionExport->setText(QCoreApplication::translate("GraphicEQFilterGUI", "Export", nullptr));
        actionInvertResponse->setText(QCoreApplication::translate("GraphicEQFilterGUI", "Invert response", nullptr));
        actionNormalizeResponse->setText(QCoreApplication::translate("GraphicEQFilterGUI", "Normalize response", nullptr));
        actionResetResponse->setText(QCoreApplication::translate("GraphicEQFilterGUI", "Reset response", nullptr));
        label->setText(QCoreApplication::translate("GraphicEQFilterGUI", "Graphic EQ:", nullptr));
        radioButton15->setText(QCoreApplication::translate("GraphicEQFilterGUI", "15-band", nullptr));
        radioButton31->setText(QCoreApplication::translate("GraphicEQFilterGUI", "31-band", nullptr));
        radioButtonVar->setText(QCoreApplication::translate("GraphicEQFilterGUI", "variable", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("GraphicEQFilterGUI", "Freq.", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("GraphicEQFilterGUI", "Gain", nullptr));
        (void)GraphicEQFilterGUI;
    } // retranslateUi

};

namespace Ui {
    class GraphicEQFilterGUI: public Ui_GraphicEQFilterGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICEQFILTERGUI_H
