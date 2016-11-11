/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTextEdit *outDeeplinks;
    QPushButton *apkSelect;
    QLabel *label;
    QLabel *label_2;
    QPushButton *extract;
    QLabel *label_3;
    QTextEdit *processResult;
    QLabel *label_4;
    QLabel *selectedFile;
    QCheckBox *asIntent;
    QCheckBox *clearCache;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(778, 647);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        outDeeplinks = new QTextEdit(centralWidget);
        outDeeplinks->setObjectName(QStringLiteral("outDeeplinks"));
        outDeeplinks->setGeometry(QRect(30, 320, 721, 251));
        outDeeplinks->setReadOnly(true);
        apkSelect = new QPushButton(centralWidget);
        apkSelect->setObjectName(QStringLiteral("apkSelect"));
        apkSelect->setGeometry(QRect(50, 20, 171, 24));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 16, 24));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 60, 16, 24));
        extract = new QPushButton(centralWidget);
        extract->setObjectName(QStringLiteral("extract"));
        extract->setGeometry(QRect(50, 60, 171, 24));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 300, 131, 16));
        processResult = new QTextEdit(centralWidget);
        processResult->setObjectName(QStringLiteral("processResult"));
        processResult->setGeometry(QRect(30, 130, 721, 160));
        processResult->setUndoRedoEnabled(false);
        processResult->setReadOnly(true);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 110, 60, 16));
        selectedFile = new QLabel(centralWidget);
        selectedFile->setObjectName(QStringLiteral("selectedFile"));
        selectedFile->setGeometry(QRect(230, 20, 511, 24));
        asIntent = new QCheckBox(centralWidget);
        asIntent->setObjectName(QStringLiteral("asIntent"));
        asIntent->setGeometry(QRect(230, 60, 161, 24));
        clearCache = new QCheckBox(centralWidget);
        clearCache->setObjectName(QStringLiteral("clearCache"));
        clearCache->setGeometry(QRect(230, 90, 161, 24));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        apkSelect->setText(QApplication::translate("MainWindow", "Select APK", 0));
        label->setText(QApplication::translate("MainWindow", "1.", 0));
        label_2->setText(QApplication::translate("MainWindow", "2.", 0));
        extract->setText(QApplication::translate("MainWindow", "Extract", 0));
        label_3->setText(QApplication::translate("MainWindow", "Possible deeplinks", 0));
        label_4->setText(QApplication::translate("MainWindow", "Output", 0));
        selectedFile->setText(QString());
        asIntent->setText(QApplication::translate("MainWindow", "as \"intent\"", 0));
        clearCache->setText(QApplication::translate("MainWindow", "overwrite cache", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
