/********************************************************************************
** Form generated from reading UI file 'manualentrywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANUALENTRYWINDOW_H
#define UI_MANUALENTRYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_manualEntryWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *Array;
    QPushButton *pushButton;

    void setupUi(QDialog *manualEntryWindow)
    {
        if (manualEntryWindow->objectName().isEmpty())
            manualEntryWindow->setObjectName(QString::fromUtf8("manualEntryWindow"));
        manualEntryWindow->resize(300, 200);
        manualEntryWindow->setMinimumSize(QSize(300, 200));
        manualEntryWindow->setMaximumSize(QSize(600, 400));
        verticalLayout = new QVBoxLayout(manualEntryWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(manualEntryWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 25));
        label->setMaximumSize(QSize(16777215, 25));
        QFont font;
        font.setFamily(QString::fromUtf8("Calibri"));
        label->setFont(font);

        verticalLayout->addWidget(label);

        Array = new QLineEdit(manualEntryWindow);
        Array->setObjectName(QString::fromUtf8("Array"));

        verticalLayout->addWidget(Array);

        pushButton = new QPushButton(manualEntryWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(100, 0));
        pushButton->setMaximumSize(QSize(100, 16777215));

        verticalLayout->addWidget(pushButton);


        retranslateUi(manualEntryWindow);

        QMetaObject::connectSlotsByName(manualEntryWindow);
    } // setupUi

    void retranslateUi(QDialog *manualEntryWindow)
    {
        manualEntryWindow->setWindowTitle(QApplication::translate("manualEntryWindow", "Dialog", nullptr));
        label->setText(QApplication::translate("manualEntryWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\207\320\270\321\201\320\273\320\260 \321\207\320\265\321\200\320\265\320\267 \320\277\321\200\320\276\320\261\320\265\320\273</span></p></body></html>", nullptr));
        pushButton->setText(QApplication::translate("manualEntryWindow", "\320\223\320\276\321\202\320\276\320\262\320\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class manualEntryWindow: public Ui_manualEntryWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANUALENTRYWINDOW_H
