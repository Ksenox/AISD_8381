/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *arrayCreation;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLineEdit *Array;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(777, 294);
        MainWindow->setMinimumSize(QSize(777, 294));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(0, 0));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(315, 0));
        label->setMaximumSize(QSize(16777215, 25));
        QFont font;
        font.setFamily(QString::fromUtf8("Calibri"));
        label->setFont(font);

        horizontalLayout->addWidget(label);

        arrayCreation = new QPushButton(centralwidget);
        arrayCreation->setObjectName(QString::fromUtf8("arrayCreation"));
        arrayCreation->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(arrayCreation);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(600, 40));
        label_2->setMaximumSize(QSize(300, 40));
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        Array = new QLineEdit(centralwidget);
        Array->setObjectName(QString::fromUtf8("Array"));
        Array->setMaxLength(300);

        verticalLayout->addWidget(Array);


        verticalLayout_2->addLayout(verticalLayout);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(91);
        sizePolicy1.setVerticalStretch(100);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setMaximumSize(QSize(100, 16777215));
        pushButton->setCursor(QCursor(Qt::ArrowCursor));
        pushButton->setMouseTracking(false);

        verticalLayout_2->addWidget(pushButton, 0, Qt::AlignRight);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 777, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">\320\222 \321\201\320\273\321\203\321\207\320\260\320\265, \320\265\321\201\320\273\320\270 \320\262\321\213 \321\205\320\276\321\202\320\270\321\202\320\265 \321\201\320\263\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\274\320\260\321\201\321\201\320\270\320\262 \321\201\320\273\321\203\321\207\320\260\320\271\320\275\321\213\320\274 \320\276\320\261\321\200\320\260\320\267\320\276\320\274 \320\275\320\260\320\266\320\274\320\270\321\202\320\265 \320\275\320\260 \320\272\320\275\320\276\320\277\320\272\321\203:</span></p><p><span style=\" font-size:10pt;\"><br/></span></p><p><span style=\" font-size:10pt;\"><br/></span></p></body></html>", nullptr));
        arrayCreation->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\270\320\273\320\270 \320\276\321\202\321\200\320\265\320\264\320\260\320\272\321\202\320\270\321\200\321\203\320\271\321\202\320\265 \320\274\320\260\321\201\321\201\320\270\320\262, \320\272\320\276\321\202\320\276\321\200\321\213\320\271 \320\261\321\213\320\273 \321\201\320\263\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\320\275 \321\201\320\273\321\203\321\207\320\260\320\271\320\275\320\276.<br/>\320\247\320\270\321\201\320\273\320\260 \320\264\320\276\320\273\320\266\320\275\321\213 \320\261\321\213\321\202\321\214 \320\262\320\262\320\265\320\264\320\265\320\275\321\213 \321\201\321\202\321\200\320\276\320\263\320\276 \321\207\320\265\321\200\320\265\320\267 \320\276\320\264\320\270\320\275 \320\277\321\200\320\276\320\261\320\265\320\273.</span></p></body></html>", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
