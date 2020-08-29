/********************************************************************************
** Form generated from reading UI file 'DeviceFilterGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICEFILTERGUI_H
#define UI_DEVICEFILTERGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeviceFilterGUI
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QWidget *DeviceFilterGUI)
    {
        if (DeviceFilterGUI->objectName().isEmpty())
            DeviceFilterGUI->setObjectName(QString::fromUtf8("DeviceFilterGUI"));
        DeviceFilterGUI->resize(400, 71);
        DeviceFilterGUI->setWindowTitle(QString::fromUtf8(""));
        gridLayout = new QGridLayout(DeviceFilterGUI);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        treeWidget = new QTreeWidget(DeviceFilterGUI);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(2, QString::fromUtf8("3"));
        __qtreewidgetitem->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy);
        treeWidget->setBaseSize(QSize(0, 10));
        treeWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        treeWidget->setRootIsDecorated(false);
        treeWidget->setColumnCount(3);

        gridLayout->addWidget(treeWidget, 0, 3, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(DeviceFilterGUI);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        pushButton = new QPushButton(DeviceFilterGUI);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        gridLayout->addLayout(verticalLayout, 0, 2, 1, 1);


        retranslateUi(DeviceFilterGUI);

        QMetaObject::connectSlotsByName(DeviceFilterGUI);
    } // setupUi

    void retranslateUi(QWidget *DeviceFilterGUI)
    {
        label->setText(QCoreApplication::translate("DeviceFilterGUI", "Selected devices:", nullptr));
        pushButton->setText(QCoreApplication::translate("DeviceFilterGUI", "Change...", nullptr));
        (void)DeviceFilterGUI;
    } // retranslateUi

};

namespace Ui {
    class DeviceFilterGUI: public Ui_DeviceFilterGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEFILTERGUI_H
