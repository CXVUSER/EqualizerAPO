/********************************************************************************
** Form generated from reading UI file 'ConvolutionFilterGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONVOLUTIONFILTERGUI_H
#define UI_CONVOLUTIONFILTERGUI_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "Editor/widgets/ResizingLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_ConvolutionFilterGUI
{
public:
    QGridLayout *gridLayout;
    QToolButton *selectFileToolButton;
    QSpacerItem *horizontalSpacer;
    QLabel *convolutionLabel;
    ResizingLineEdit *pathLineEdit;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *labelSampleRate;
    QLabel *labelLengthValue;
    QLabel *labelError;
    QLabel *labelLength;
    QLabel *labelSampleRateValue;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *ConvolutionFilterGUI)
    {
        if (ConvolutionFilterGUI->objectName().isEmpty())
            ConvolutionFilterGUI->setObjectName(QString::fromUtf8("ConvolutionFilterGUI"));
        ConvolutionFilterGUI->resize(665, 79);
        ConvolutionFilterGUI->setWindowTitle(QString::fromUtf8(""));
        gridLayout = new QGridLayout(ConvolutionFilterGUI);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        selectFileToolButton = new QToolButton(ConvolutionFilterGUI);
        selectFileToolButton->setObjectName(QString::fromUtf8("selectFileToolButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/document-open.ico"), QSize(), QIcon::Normal, QIcon::Off);
        selectFileToolButton->setIcon(icon);

        gridLayout->addWidget(selectFileToolButton, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(123, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 4, 1, 1);

        convolutionLabel = new QLabel(ConvolutionFilterGUI);
        convolutionLabel->setObjectName(QString::fromUtf8("convolutionLabel"));

        gridLayout->addWidget(convolutionLabel, 0, 0, 1, 1);

        pathLineEdit = new ResizingLineEdit(ConvolutionFilterGUI);
        pathLineEdit->setObjectName(QString::fromUtf8("pathLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pathLineEdit->sizePolicy().hasHeightForWidth());
        pathLineEdit->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pathLineEdit, 0, 1, 1, 1);

        groupBox = new QGroupBox(ConvolutionFilterGUI);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        labelSampleRate = new QLabel(groupBox);
        labelSampleRate->setObjectName(QString::fromUtf8("labelSampleRate"));

        gridLayout_2->addWidget(labelSampleRate, 0, 3, 1, 1);

        labelLengthValue = new QLabel(groupBox);
        labelLengthValue->setObjectName(QString::fromUtf8("labelLengthValue"));

        gridLayout_2->addWidget(labelLengthValue, 0, 1, 1, 1);

        labelError = new QLabel(groupBox);
        labelError->setObjectName(QString::fromUtf8("labelError"));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        labelError->setPalette(palette);
        labelError->setText(QString::fromUtf8(""));

        gridLayout_2->addWidget(labelError, 1, 0, 1, 5);

        labelLength = new QLabel(groupBox);
        labelLength->setObjectName(QString::fromUtf8("labelLength"));

        gridLayout_2->addWidget(labelLength, 0, 0, 1, 1);

        labelSampleRateValue = new QLabel(groupBox);
        labelSampleRateValue->setObjectName(QString::fromUtf8("labelSampleRateValue"));

        gridLayout_2->addWidget(labelSampleRateValue, 0, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(5, 1, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 2, 1, 1);


        gridLayout->addWidget(groupBox, 0, 3, 1, 1);

        gridLayout->setColumnStretch(4, 1);

        retranslateUi(ConvolutionFilterGUI);

        QMetaObject::connectSlotsByName(ConvolutionFilterGUI);
    } // setupUi

    void retranslateUi(QWidget *ConvolutionFilterGUI)
    {
        selectFileToolButton->setText(QCoreApplication::translate("ConvolutionFilterGUI", "Select file", nullptr));
        convolutionLabel->setText(QCoreApplication::translate("ConvolutionFilterGUI", "Convolution with impulse response:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ConvolutionFilterGUI", "File information", nullptr));
        labelSampleRate->setText(QCoreApplication::translate("ConvolutionFilterGUI", "Sample rate:", nullptr));
        labelLengthValue->setText(QCoreApplication::translate("ConvolutionFilterGUI", "No file selected", nullptr));
        labelLength->setText(QCoreApplication::translate("ConvolutionFilterGUI", "Length:", nullptr));
        labelSampleRateValue->setText(QCoreApplication::translate("ConvolutionFilterGUI", "No file selected", nullptr));
        (void)ConvolutionFilterGUI;
    } // retranslateUi

};

namespace Ui {
    class ConvolutionFilterGUI: public Ui_ConvolutionFilterGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONVOLUTIONFILTERGUI_H
