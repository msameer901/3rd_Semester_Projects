/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QLabel *label;
    QPushButton *menuBtn;
    QFrame *sideMenu;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QStackedWidget *stackedWidget;
    QWidget *pageM1;
    QLineEdit *m1InputBar;
    QComboBox *comboM1Part;
    QPushButton *btnM1Enter;
    QTextEdit *m1Output;
    QWidget *pageM3;
    QGridLayout *gridLayout_2;
    QComboBox *comboM3Part;
    QLineEdit *m3InputBar;
    QPushButton *btnM3Enter;
    QTextEdit *m3Output;
    QWidget *pageM2;
    QGridLayout *gridLayout;
    QComboBox *comboM2Part;
    QLabel *labelCategories;
    QLineEdit *inputDescription;
    QPushButton *btnClassify;
    QTextEdit *lblResult;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(9, -1, 781, 51));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(190, 10, 411, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Nirmala UI")});
        font.setPointSize(10);
        label->setFont(font);
        label->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        menuBtn = new QPushButton(frame);
        menuBtn->setObjectName("menuBtn");
        menuBtn->setGeometry(QRect(10, 10, 41, 29));
        sideMenu = new QFrame(centralwidget);
        sideMenu->setObjectName("sideMenu");
        sideMenu->setGeometry(QRect(9, 69, 231, 491));
        sideMenu->setMinimumSize(QSize(231, 0));
        sideMenu->setFrameShape(QFrame::Shape::StyledPanel);
        sideMenu->setFrameShadow(QFrame::Shadow::Raised);
        pushButton = new QPushButton(sideMenu);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 80, 201, 31));
        QFont font1;
        font1.setPointSize(7);
        pushButton->setFont(font1);
        pushButton_2 = new QPushButton(sideMenu);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 190, 201, 31));
        pushButton_2->setFont(font1);
        pushButton_3 = new QPushButton(sideMenu);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(10, 300, 201, 31));
        pushButton_3->setFont(font1);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(260, 70, 278, 467));
        pageM1 = new QWidget();
        pageM1->setObjectName("pageM1");
        m1InputBar = new QLineEdit(pageM1);
        m1InputBar->setObjectName("m1InputBar");
        m1InputBar->setGeometry(QRect(30, 170, 381, 41));
        comboM1Part = new QComboBox(pageM1);
        comboM1Part->setObjectName("comboM1Part");
        comboM1Part->setGeometry(QRect(30, 70, 411, 51));
        btnM1Enter = new QPushButton(pageM1);
        btnM1Enter->setObjectName("btnM1Enter");
        btnM1Enter->setGeometry(QRect(30, 230, 161, 41));
        m1Output = new QTextEdit(pageM1);
        m1Output->setObjectName("m1Output");
        m1Output->setGeometry(QRect(30, 280, 451, 191));
        stackedWidget->addWidget(pageM1);
        pageM3 = new QWidget();
        pageM3->setObjectName("pageM3");
        gridLayout_2 = new QGridLayout(pageM3);
        gridLayout_2->setObjectName("gridLayout_2");
        comboM3Part = new QComboBox(pageM3);
        comboM3Part->setObjectName("comboM3Part");

        gridLayout_2->addWidget(comboM3Part, 0, 0, 1, 1);

        m3InputBar = new QLineEdit(pageM3);
        m3InputBar->setObjectName("m3InputBar");

        gridLayout_2->addWidget(m3InputBar, 1, 0, 1, 1);

        btnM3Enter = new QPushButton(pageM3);
        btnM3Enter->setObjectName("btnM3Enter");

        gridLayout_2->addWidget(btnM3Enter, 2, 0, 1, 1);

        m3Output = new QTextEdit(pageM3);
        m3Output->setObjectName("m3Output");

        gridLayout_2->addWidget(m3Output, 3, 0, 1, 1);

        stackedWidget->addWidget(pageM3);
        pageM2 = new QWidget();
        pageM2->setObjectName("pageM2");
        gridLayout = new QGridLayout(pageM2);
        gridLayout->setObjectName("gridLayout");
        comboM2Part = new QComboBox(pageM2);
        comboM2Part->setObjectName("comboM2Part");

        gridLayout->addWidget(comboM2Part, 0, 0, 1, 1);

        labelCategories = new QLabel(pageM2);
        labelCategories->setObjectName("labelCategories");

        gridLayout->addWidget(labelCategories, 1, 0, 1, 1);

        inputDescription = new QLineEdit(pageM2);
        inputDescription->setObjectName("inputDescription");

        gridLayout->addWidget(inputDescription, 2, 0, 1, 1);

        btnClassify = new QPushButton(pageM2);
        btnClassify->setObjectName("btnClassify");

        gridLayout->addWidget(btnClassify, 3, 0, 1, 1);

        lblResult = new QTextEdit(pageM2);
        lblResult->setObjectName("lblResult");
        lblResult->setReadOnly(true);

        gridLayout->addWidget(lblResult, 4, 0, 1, 1);

        stackedWidget->addWidget(pageM2);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Intelligent Banking Management System (IBMS)", nullptr));
        menuBtn->setText(QCoreApplication::translate("MainWindow", "\342\211\241", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Transaction & Account Management", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Transaction Classification", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Customer Queue & Event Simulation ", nullptr));
        m1InputBar->setText(QString());
        m1InputBar->setPlaceholderText(QCoreApplication::translate("MainWindow", "ID, Name, Balance", nullptr));
        btnM1Enter->setText(QCoreApplication::translate("MainWindow", "Enter", nullptr));
        btnM3Enter->setText(QCoreApplication::translate("MainWindow", "Enter Queue", nullptr));
        labelCategories->setText(QCoreApplication::translate("MainWindow", "Categories\n"
"0 - Food\n"
"1 - Utilities\n"
" 2 - Education\n"
" 3 - Government\n"
" 4 - Others\n"
"", nullptr));
        inputDescription->setPlaceholderText(QCoreApplication::translate("MainWindow", "TxID, Description (e.g., 1, Pizza)", nullptr));
        btnClassify->setText(QCoreApplication::translate("MainWindow", "Enter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
