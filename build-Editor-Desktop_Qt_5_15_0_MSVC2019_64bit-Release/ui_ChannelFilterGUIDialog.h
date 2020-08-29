/********************************************************************************
** Form generated from reading UI file 'ChannelFilterGUIDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANNELFILTERGUIDIALOG_H
#define UI_CHANNELFILTERGUIDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChannelFilterGUIDialog
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *allChannelsCheckBox;
    QGroupBox *positionsGroupBox;
    QGridLayout *gridLayout_2;
    QCheckBox *sideRightCheckBox;
    QCheckBox *centerCheckBox;
    QCheckBox *subWooferCheckBox;
    QCheckBox *leftCheckBox;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QCheckBox *rearLeftCheckBox;
    QCheckBox *rearRightCheckBox;
    QSpacerItem *horizontalSpacer_2;
    QWidget *page_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *rearCenterCheckBox;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *sideLeftCheckBox;
    QCheckBox *rightCheckBox;
    QGroupBox *additionalChannelsGroupBox;
    QGridLayout *gridLayout;
    QToolButton *removeButton;
    QToolButton *addButton;
    QSpacerItem *horizontalSpacer_5;
    QListWidget *listWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ChannelFilterGUIDialog)
    {
        if (ChannelFilterGUIDialog->objectName().isEmpty())
            ChannelFilterGUIDialog->setObjectName(QString::fromUtf8("ChannelFilterGUIDialog"));
        ChannelFilterGUIDialog->resize(375, 394);
        verticalLayout = new QVBoxLayout(ChannelFilterGUIDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        allChannelsCheckBox = new QCheckBox(ChannelFilterGUIDialog);
        allChannelsCheckBox->setObjectName(QString::fromUtf8("allChannelsCheckBox"));

        verticalLayout->addWidget(allChannelsCheckBox);

        positionsGroupBox = new QGroupBox(ChannelFilterGUIDialog);
        positionsGroupBox->setObjectName(QString::fromUtf8("positionsGroupBox"));
        gridLayout_2 = new QGridLayout(positionsGroupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        sideRightCheckBox = new QCheckBox(positionsGroupBox);
        sideRightCheckBox->setObjectName(QString::fromUtf8("sideRightCheckBox"));

        gridLayout_2->addWidget(sideRightCheckBox, 3, 2, 1, 1);

        centerCheckBox = new QCheckBox(positionsGroupBox);
        centerCheckBox->setObjectName(QString::fromUtf8("centerCheckBox"));

        gridLayout_2->addWidget(centerCheckBox, 1, 1, 1, 1);

        subWooferCheckBox = new QCheckBox(positionsGroupBox);
        subWooferCheckBox->setObjectName(QString::fromUtf8("subWooferCheckBox"));

        gridLayout_2->addWidget(subWooferCheckBox, 1, 2, 1, 1);

        leftCheckBox = new QCheckBox(positionsGroupBox);
        leftCheckBox->setObjectName(QString::fromUtf8("leftCheckBox"));

        gridLayout_2->addWidget(leftCheckBox, 2, 0, 1, 1);

        stackedWidget = new QStackedWidget(positionsGroupBox);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        horizontalLayout_2 = new QHBoxLayout(page);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        rearLeftCheckBox = new QCheckBox(page);
        rearLeftCheckBox->setObjectName(QString::fromUtf8("rearLeftCheckBox"));

        horizontalLayout_2->addWidget(rearLeftCheckBox);

        rearRightCheckBox = new QCheckBox(page);
        rearRightCheckBox->setObjectName(QString::fromUtf8("rearRightCheckBox"));

        horizontalLayout_2->addWidget(rearRightCheckBox);

        horizontalSpacer_2 = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        horizontalLayout = new QHBoxLayout(page_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        rearCenterCheckBox = new QCheckBox(page_2);
        rearCenterCheckBox->setObjectName(QString::fromUtf8("rearCenterCheckBox"));

        horizontalLayout->addWidget(rearCenterCheckBox);

        horizontalSpacer_4 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        stackedWidget->addWidget(page_2);

        gridLayout_2->addWidget(stackedWidget, 4, 0, 2, 3);

        sideLeftCheckBox = new QCheckBox(positionsGroupBox);
        sideLeftCheckBox->setObjectName(QString::fromUtf8("sideLeftCheckBox"));

        gridLayout_2->addWidget(sideLeftCheckBox, 3, 0, 1, 1);

        rightCheckBox = new QCheckBox(positionsGroupBox);
        rightCheckBox->setObjectName(QString::fromUtf8("rightCheckBox"));

        gridLayout_2->addWidget(rightCheckBox, 2, 2, 1, 1);


        verticalLayout->addWidget(positionsGroupBox);

        additionalChannelsGroupBox = new QGroupBox(ChannelFilterGUIDialog);
        additionalChannelsGroupBox->setObjectName(QString::fromUtf8("additionalChannelsGroupBox"));
        gridLayout = new QGridLayout(additionalChannelsGroupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        removeButton = new QToolButton(additionalChannelsGroupBox);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/list-remove-red.ico"), QSize(), QIcon::Normal, QIcon::Off);
        removeButton->setIcon(icon);

        gridLayout->addWidget(removeButton, 2, 2, 1, 1);

        addButton = new QToolButton(additionalChannelsGroupBox);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/list-add-green.ico"), QSize(), QIcon::Normal, QIcon::Off);
        addButton->setIcon(icon1);

        gridLayout->addWidget(addButton, 2, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 2, 0, 1, 1);

        listWidget = new QListWidget(additionalChannelsGroupBox);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        listWidget->setDragEnabled(true);
        listWidget->setDragDropMode(QAbstractItemView::InternalMove);
        listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

        gridLayout->addWidget(listWidget, 0, 0, 1, 3);


        verticalLayout->addWidget(additionalChannelsGroupBox);

        buttonBox = new QDialogButtonBox(ChannelFilterGUIDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ChannelFilterGUIDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ChannelFilterGUIDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ChannelFilterGUIDialog, SLOT(reject()));

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ChannelFilterGUIDialog);
    } // setupUi

    void retranslateUi(QDialog *ChannelFilterGUIDialog)
    {
        ChannelFilterGUIDialog->setWindowTitle(QCoreApplication::translate("ChannelFilterGUIDialog", "Channel selection", nullptr));
        allChannelsCheckBox->setText(QCoreApplication::translate("ChannelFilterGUIDialog", "Select all channels", nullptr));
        positionsGroupBox->setTitle(QCoreApplication::translate("ChannelFilterGUIDialog", "Speaker positions", nullptr));
        sideRightCheckBox->setText(QCoreApplication::translate("ChannelFilterGUIDialog", "SR (Side right)", nullptr));
        centerCheckBox->setText(QCoreApplication::translate("ChannelFilterGUIDialog", "C (Center)", nullptr));
        subWooferCheckBox->setText(QCoreApplication::translate("ChannelFilterGUIDialog", "LFE (Subwoofer)", nullptr));
        leftCheckBox->setText(QCoreApplication::translate("ChannelFilterGUIDialog", "L (Left)", nullptr));
        rearLeftCheckBox->setText(QCoreApplication::translate("ChannelFilterGUIDialog", "RL (Rear left)", nullptr));
        rearRightCheckBox->setText(QCoreApplication::translate("ChannelFilterGUIDialog", "RR (Rear right)", nullptr));
        rearCenterCheckBox->setText(QCoreApplication::translate("ChannelFilterGUIDialog", "RC (Rear center)", nullptr));
        sideLeftCheckBox->setText(QCoreApplication::translate("ChannelFilterGUIDialog", "SL (Side left)", nullptr));
        rightCheckBox->setText(QCoreApplication::translate("ChannelFilterGUIDialog", "R (Right)", nullptr));
        additionalChannelsGroupBox->setTitle(QCoreApplication::translate("ChannelFilterGUIDialog", "Additional channels", nullptr));
        removeButton->setText(QCoreApplication::translate("ChannelFilterGUIDialog", "Remove channel", nullptr));
        addButton->setText(QCoreApplication::translate("ChannelFilterGUIDialog", "Add channel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChannelFilterGUIDialog: public Ui_ChannelFilterGUIDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANNELFILTERGUIDIALOG_H
