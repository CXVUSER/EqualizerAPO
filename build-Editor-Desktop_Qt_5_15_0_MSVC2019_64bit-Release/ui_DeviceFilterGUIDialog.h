/********************************************************************************
** Form generated from reading UI file 'DeviceFilterGUIDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICEFILTERGUIDIALOG_H
#define UI_DEVICEFILTERGUIDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_DeviceFilterGUIDialog
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget;
    QCheckBox *allDevicesCheckBox;
    QDialogButtonBox *buttonBox;
    QCheckBox *showOnlyInstalledCheckBox;

    void setupUi(QDialog *DeviceFilterGUIDialog)
    {
        if (DeviceFilterGUIDialog->objectName().isEmpty())
            DeviceFilterGUIDialog->setObjectName(QString::fromUtf8("DeviceFilterGUIDialog"));
        DeviceFilterGUIDialog->resize(500, 350);
        gridLayout = new QGridLayout(DeviceFilterGUIDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        treeWidget = new QTreeWidget(DeviceFilterGUIDialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(2, QString::fromUtf8("3"));
        __qtreewidgetitem->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setColumnCount(3);

        gridLayout->addWidget(treeWidget, 1, 0, 1, 1);

        allDevicesCheckBox = new QCheckBox(DeviceFilterGUIDialog);
        allDevicesCheckBox->setObjectName(QString::fromUtf8("allDevicesCheckBox"));

        gridLayout->addWidget(allDevicesCheckBox, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DeviceFilterGUIDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 1);

        showOnlyInstalledCheckBox = new QCheckBox(DeviceFilterGUIDialog);
        showOnlyInstalledCheckBox->setObjectName(QString::fromUtf8("showOnlyInstalledCheckBox"));
        showOnlyInstalledCheckBox->setChecked(true);

        gridLayout->addWidget(showOnlyInstalledCheckBox, 2, 0, 1, 1);


        retranslateUi(DeviceFilterGUIDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), DeviceFilterGUIDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DeviceFilterGUIDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(DeviceFilterGUIDialog);
    } // setupUi

    void retranslateUi(QDialog *DeviceFilterGUIDialog)
    {
        DeviceFilterGUIDialog->setWindowTitle(QCoreApplication::translate("DeviceFilterGUIDialog", "Device selection", nullptr));
        allDevicesCheckBox->setText(QCoreApplication::translate("DeviceFilterGUIDialog", "Select all devices", nullptr));
        showOnlyInstalledCheckBox->setText(QCoreApplication::translate("DeviceFilterGUIDialog", "Show only devices with APO installed", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeviceFilterGUIDialog: public Ui_DeviceFilterGUIDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEFILTERGUIDIALOG_H
