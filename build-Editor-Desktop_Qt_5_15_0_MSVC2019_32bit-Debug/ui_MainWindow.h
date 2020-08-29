/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "Editor/AnalysisPlotView.h"
#include "Editor/widgets/ExponentialSpinBox.h"
#include "Editor/widgets/MiddleClickTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionExit;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionDelete;
    QAction *actionToolbar;
    QAction *actionAnalysisPanel;
    QAction *actionResetAllGlobalPreferences;
    QAction *actionResetAllFileSpecificPreferences;
    QAction *actionSelectAll;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    MiddleClickTabWidget *tabWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuSettings;
    QMenu *menuLanguage;
    QToolBar *mainToolBar;
    QDockWidget *analysisDockWidget;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QLabel *resolutionLabel;
    QLabel *analysisChannelLabel;
    QComboBox *analysisChannelComboBox;
    ExponentialSpinBox *resolutionSpinBox;
    QLabel *startFromLabel;
    QComboBox *startFromComboBox;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QLabel *initTimeValueLabel;
    QLabel *cpuUsageLabel;
    QLabel *initTimeLabel;
    QLabel *cpuUsageValueLabel;
    QLabel *latencyValueLabel;
    QLabel *latencyLabel;
    QLabel *peakGainlabel;
    QLabel *peakGainValueLabel;
    AnalysisPlotView *graphicsView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 768);
        MainWindow->setWindowTitle(QString::fromUtf8(""));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/document-new.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
#if QT_CONFIG(shortcut)
        actionNew->setShortcut(QString::fromUtf8("Ctrl+N"));
#endif // QT_CONFIG(shortcut)
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/document-open.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QString::fromUtf8("Ctrl+O"));
#endif // QT_CONFIG(shortcut)
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/document-save.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QString::fromUtf8("Ctrl+S"));
#endif // QT_CONFIG(shortcut)
        actionSaveAs = new QAction(MainWindow);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/document-save-as.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveAs->setIcon(icon3);
#if QT_CONFIG(shortcut)
        actionSaveAs->setShortcut(QString::fromUtf8(""));
#endif // QT_CONFIG(shortcut)
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QString::fromUtf8("Alt+F4"));
#endif // QT_CONFIG(shortcut)
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/edit-cut.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionCut->setIcon(icon4);
#if QT_CONFIG(shortcut)
        actionCut->setShortcut(QString::fromUtf8("Ctrl+X"));
#endif // QT_CONFIG(shortcut)
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/edit-copy.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon5);
#if QT_CONFIG(shortcut)
        actionCopy->setShortcut(QString::fromUtf8("Ctrl+C"));
#endif // QT_CONFIG(shortcut)
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/edit-paste.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionPaste->setIcon(icon6);
#if QT_CONFIG(shortcut)
        actionPaste->setShortcut(QString::fromUtf8("Ctrl+V"));
#endif // QT_CONFIG(shortcut)
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/edit-delete.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon7);
#if QT_CONFIG(shortcut)
        actionDelete->setShortcut(QString::fromUtf8(""));
#endif // QT_CONFIG(shortcut)
        actionToolbar = new QAction(MainWindow);
        actionToolbar->setObjectName(QString::fromUtf8("actionToolbar"));
        actionToolbar->setCheckable(true);
        actionAnalysisPanel = new QAction(MainWindow);
        actionAnalysisPanel->setObjectName(QString::fromUtf8("actionAnalysisPanel"));
        actionAnalysisPanel->setCheckable(true);
        actionResetAllGlobalPreferences = new QAction(MainWindow);
        actionResetAllGlobalPreferences->setObjectName(QString::fromUtf8("actionResetAllGlobalPreferences"));
        actionResetAllFileSpecificPreferences = new QAction(MainWindow);
        actionResetAllFileSpecificPreferences->setObjectName(QString::fromUtf8("actionResetAllFileSpecificPreferences"));
        actionSelectAll = new QAction(MainWindow);
        actionSelectAll->setObjectName(QString::fromUtf8("actionSelectAll"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/edit-select-all.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelectAll->setIcon(icon8);
#if QT_CONFIG(shortcut)
        actionSelectAll->setShortcut(QString::fromUtf8("Ctrl+A"));
#endif // QT_CONFIG(shortcut)
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new MiddleClickTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setDocumentMode(true);
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(true);

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuLanguage = new QMenu(menuSettings);
        menuLanguage->setObjectName(QString::fromUtf8("menuLanguage"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        analysisDockWidget = new QDockWidget(MainWindow);
        analysisDockWidget->setObjectName(QString::fromUtf8("analysisDockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout_2 = new QGridLayout(dockWidgetContents);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(1);
        gridLayout_2->setVerticalSpacing(3);
        gridLayout_2->setContentsMargins(1, 0, 1, 1);
        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setVerticalSpacing(1);
        gridLayout_3->setContentsMargins(-1, 3, -1, 3);
        resolutionLabel = new QLabel(groupBox);
        resolutionLabel->setObjectName(QString::fromUtf8("resolutionLabel"));

        gridLayout_3->addWidget(resolutionLabel, 3, 0, 1, 1);

        analysisChannelLabel = new QLabel(groupBox);
        analysisChannelLabel->setObjectName(QString::fromUtf8("analysisChannelLabel"));

        gridLayout_3->addWidget(analysisChannelLabel, 2, 0, 1, 1);

        analysisChannelComboBox = new QComboBox(groupBox);
        analysisChannelComboBox->setObjectName(QString::fromUtf8("analysisChannelComboBox"));

        gridLayout_3->addWidget(analysisChannelComboBox, 2, 1, 1, 1);

        resolutionSpinBox = new ExponentialSpinBox(groupBox);
        resolutionSpinBox->setObjectName(QString::fromUtf8("resolutionSpinBox"));
        resolutionSpinBox->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        resolutionSpinBox->setKeyboardTracking(false);
        resolutionSpinBox->setMinimum(128);
        resolutionSpinBox->setMaximum(8388608);
        resolutionSpinBox->setValue(65536);

        gridLayout_3->addWidget(resolutionSpinBox, 3, 1, 1, 1);

        startFromLabel = new QLabel(groupBox);
        startFromLabel->setObjectName(QString::fromUtf8("startFromLabel"));

        gridLayout_3->addWidget(startFromLabel, 1, 0, 1, 1);

        startFromComboBox = new QComboBox(groupBox);
        startFromComboBox->addItem(QString::fromUtf8("config.txt"));
        startFromComboBox->addItem(QString());
        startFromComboBox->setObjectName(QString::fromUtf8("startFromComboBox"));

        gridLayout_3->addWidget(startFromComboBox, 1, 1, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(dockWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(-1, 6, -1, -1);
        initTimeValueLabel = new QLabel(groupBox_2);
        initTimeValueLabel->setObjectName(QString::fromUtf8("initTimeValueLabel"));
        initTimeValueLabel->setText(QString::fromUtf8(""));

        gridLayout_4->addWidget(initTimeValueLabel, 2, 1, 1, 1);

        cpuUsageLabel = new QLabel(groupBox_2);
        cpuUsageLabel->setObjectName(QString::fromUtf8("cpuUsageLabel"));

        gridLayout_4->addWidget(cpuUsageLabel, 3, 0, 1, 1);

        initTimeLabel = new QLabel(groupBox_2);
        initTimeLabel->setObjectName(QString::fromUtf8("initTimeLabel"));

        gridLayout_4->addWidget(initTimeLabel, 2, 0, 1, 1);

        cpuUsageValueLabel = new QLabel(groupBox_2);
        cpuUsageValueLabel->setObjectName(QString::fromUtf8("cpuUsageValueLabel"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 127, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        QBrush brush2(QColor(255, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        cpuUsageValueLabel->setPalette(palette);
        cpuUsageValueLabel->setText(QString::fromUtf8(""));

        gridLayout_4->addWidget(cpuUsageValueLabel, 3, 1, 1, 1);

        latencyValueLabel = new QLabel(groupBox_2);
        latencyValueLabel->setObjectName(QString::fromUtf8("latencyValueLabel"));
        latencyValueLabel->setText(QString::fromUtf8(""));

        gridLayout_4->addWidget(latencyValueLabel, 1, 1, 1, 1);

        latencyLabel = new QLabel(groupBox_2);
        latencyLabel->setObjectName(QString::fromUtf8("latencyLabel"));

        gridLayout_4->addWidget(latencyLabel, 1, 0, 1, 1);

        peakGainlabel = new QLabel(groupBox_2);
        peakGainlabel->setObjectName(QString::fromUtf8("peakGainlabel"));

        gridLayout_4->addWidget(peakGainlabel, 0, 0, 1, 1);

        peakGainValueLabel = new QLabel(groupBox_2);
        peakGainValueLabel->setObjectName(QString::fromUtf8("peakGainValueLabel"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        peakGainValueLabel->setPalette(palette1);
        peakGainValueLabel->setText(QString::fromUtf8(""));

        gridLayout_4->addWidget(peakGainValueLabel, 0, 1, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 1, 0, 1, 1);

        graphicsView = new AnalysisPlotView(dockWidgetContents);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMouseTracking(true);
        graphicsView->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);

        gridLayout_2->addWidget(graphicsView, 0, 1, 2, 1);

        analysisDockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::BottomDockWidgetArea, analysisDockWidget);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSaveAs);
        menuFile->addSeparator();
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionDelete);
        menuEdit->addSeparator();
        menuEdit->addAction(actionSelectAll);
        menuView->addAction(actionToolbar);
        menuView->addAction(actionAnalysisPanel);
        menuSettings->addAction(menuLanguage->menuAction());
        menuSettings->addSeparator();
        menuSettings->addAction(actionResetAllGlobalPreferences);
        menuSettings->addAction(actionResetAllFileSpecificPreferences);
        menuLanguage->addSeparator();
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        actionNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen->setToolTip(QCoreApplication::translate("MainWindow", "Open", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
#if QT_CONFIG(tooltip)
        actionSave->setToolTip(QCoreApplication::translate("MainWindow", "Save", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSaveAs->setText(QCoreApplication::translate("MainWindow", "Save as...", nullptr));
#if QT_CONFIG(tooltip)
        actionSaveAs->setToolTip(QCoreApplication::translate("MainWindow", "Save as...", nullptr));
#endif // QT_CONFIG(tooltip)
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionCut->setText(QCoreApplication::translate("MainWindow", "Cut", nullptr));
        actionCopy->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
        actionPaste->setText(QCoreApplication::translate("MainWindow", "Paste", nullptr));
        actionDelete->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        actionToolbar->setText(QCoreApplication::translate("MainWindow", "Toolbar", nullptr));
        actionAnalysisPanel->setText(QCoreApplication::translate("MainWindow", "Analysis panel", nullptr));
        actionResetAllGlobalPreferences->setText(QCoreApplication::translate("MainWindow", "Reset all global preferences", nullptr));
        actionResetAllFileSpecificPreferences->setText(QCoreApplication::translate("MainWindow", "Reset all file-specific preferences", nullptr));
        actionSelectAll->setText(QCoreApplication::translate("MainWindow", "Select all", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        menuLanguage->setTitle(QCoreApplication::translate("MainWindow", "Language", nullptr));
        mainToolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "Toolbar", nullptr));
        analysisDockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "Analysis panel", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        resolutionLabel->setText(QCoreApplication::translate("MainWindow", "Resolution:", nullptr));
        analysisChannelLabel->setText(QCoreApplication::translate("MainWindow", "Channel:", nullptr));
        startFromLabel->setText(QCoreApplication::translate("MainWindow", "Start from:", nullptr));
        startFromComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Current file", nullptr));

        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Estimated properties", nullptr));
        cpuUsageLabel->setText(QCoreApplication::translate("MainWindow", "CPU usage:", nullptr));
        initTimeLabel->setText(QCoreApplication::translate("MainWindow", "Init. time:", nullptr));
        latencyLabel->setText(QCoreApplication::translate("MainWindow", "Latency: ", nullptr));
        peakGainlabel->setText(QCoreApplication::translate("MainWindow", "Peak gain:", nullptr));
        (void)MainWindow;
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
