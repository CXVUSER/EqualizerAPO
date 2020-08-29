/********************************************************************************
** Form generated from reading UI file 'ChannelFilterGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANNELFILTERGUI_H
#define UI_CHANNELFILTERGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChannelFilterGUI
{
public:
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QWidget *ChannelFilterGUI)
    {
        if (ChannelFilterGUI->objectName().isEmpty())
            ChannelFilterGUI->setObjectName(QString::fromUtf8("ChannelFilterGUI"));
        ChannelFilterGUI->resize(529, 44);
        ChannelFilterGUI->setWindowTitle(QString::fromUtf8(""));
        gridLayout = new QGridLayout(ChannelFilterGUI);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QGraphicsView(ChannelFilterGUI);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMinimumSize(QSize(0, 20));
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        graphicsView->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
        graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

        gridLayout->addWidget(graphicsView, 0, 1, 2, 1);

        pushButton = new QPushButton(ChannelFilterGUI);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        label = new QLabel(ChannelFilterGUI);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(ChannelFilterGUI);

        QMetaObject::connectSlotsByName(ChannelFilterGUI);
    } // setupUi

    void retranslateUi(QWidget *ChannelFilterGUI)
    {
        pushButton->setText(QCoreApplication::translate("ChannelFilterGUI", "Change...", nullptr));
        label->setText(QCoreApplication::translate("ChannelFilterGUI", "Selected channels:", nullptr));
        (void)ChannelFilterGUI;
    } // retranslateUi

};

namespace Ui {
    class ChannelFilterGUI: public Ui_ChannelFilterGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANNELFILTERGUI_H
