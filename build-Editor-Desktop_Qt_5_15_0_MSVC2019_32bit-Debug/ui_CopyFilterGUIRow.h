/********************************************************************************
** Form generated from reading UI file 'CopyFilterGUIRow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYFILTERGUIROW_H
#define UI_COPYFILTERGUIROW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CopyFilterGUIRow
{
public:
    QHBoxLayout *horizontalLayout;
    QComboBox *modeComboBox;
    QDoubleSpinBox *factorSpinBox;
    QLabel *asteriskLabel;
    QComboBox *channelComboBox;

    void setupUi(QWidget *CopyFilterGUIRow)
    {
        if (CopyFilterGUIRow->objectName().isEmpty())
            CopyFilterGUIRow->setObjectName(QString::fromUtf8("CopyFilterGUIRow"));
        CopyFilterGUIRow->resize(523, 128);
        CopyFilterGUIRow->setWindowTitle(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(CopyFilterGUIRow);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        modeComboBox = new QComboBox(CopyFilterGUIRow);
        modeComboBox->setObjectName(QString::fromUtf8("modeComboBox"));

        horizontalLayout->addWidget(modeComboBox);

        factorSpinBox = new QDoubleSpinBox(CopyFilterGUIRow);
        factorSpinBox->setObjectName(QString::fromUtf8("factorSpinBox"));
        factorSpinBox->setDecimals(4);
        factorSpinBox->setMinimum(-99.989999999999995);
        factorSpinBox->setSingleStep(0.100000000000000);

        horizontalLayout->addWidget(factorSpinBox);

        asteriskLabel = new QLabel(CopyFilterGUIRow);
        asteriskLabel->setObjectName(QString::fromUtf8("asteriskLabel"));
        asteriskLabel->setText(QString::fromUtf8("*"));

        horizontalLayout->addWidget(asteriskLabel);

        channelComboBox = new QComboBox(CopyFilterGUIRow);
        channelComboBox->setObjectName(QString::fromUtf8("channelComboBox"));
        channelComboBox->setEditable(true);

        horizontalLayout->addWidget(channelComboBox);


        retranslateUi(CopyFilterGUIRow);

        QMetaObject::connectSlotsByName(CopyFilterGUIRow);
    } // setupUi

    void retranslateUi(QWidget *CopyFilterGUIRow)
    {
        (void)CopyFilterGUIRow;
    } // retranslateUi

};

namespace Ui {
    class CopyFilterGUIRow: public Ui_CopyFilterGUIRow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYFILTERGUIROW_H
