/********************************************************************************
** Form generated from reading UI file 'randomentrywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANDOMENTRYWINDOW_H
#define UI_RANDOMENTRYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_randomEntryWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *number;
    QPushButton *pushButton;

    void setupUi(QDialog *randomEntryWindow)
    {
        if (randomEntryWindow->objectName().isEmpty())
            randomEntryWindow->setObjectName(QString::fromUtf8("randomEntryWindow"));
        randomEntryWindow->resize(544, 200);
        randomEntryWindow->setMinimumSize(QSize(544, 200));
        randomEntryWindow->setMaximumSize(QSize(600, 400));
        verticalLayout = new QVBoxLayout(randomEntryWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        label = new QLabel(randomEntryWindow);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(16777215, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("Calibri"));
        font.setPointSize(10);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        number = new QLineEdit(randomEntryWindow);
        number->setObjectName(QString::fromUtf8("number"));
        sizePolicy.setHeightForWidth(number->sizePolicy().hasHeightForWidth());
        number->setSizePolicy(sizePolicy);
        number->setMinimumSize(QSize(40, 40));
        number->setMaximumSize(QSize(40, 40));

        horizontalLayout->addWidget(number);


        verticalLayout->addLayout(horizontalLayout);

        pushButton = new QPushButton(randomEntryWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton, 0, Qt::AlignRight);


        retranslateUi(randomEntryWindow);

        QMetaObject::connectSlotsByName(randomEntryWindow);
    } // setupUi

    void retranslateUi(QDialog *randomEntryWindow)
    {
        randomEntryWindow->setWindowTitle(QApplication::translate("randomEntryWindow", "Dialog", nullptr));
        label->setText(QApplication::translate("randomEntryWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\272\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\215\320\273\320\265\320\274\320\265\320\275\321\202\320\276\320\262, \320\272\320\276\321\202\320\276\321\200\321\213\320\265 \321\205\320\276\321\202\320\270\321\202\320\265 \321\201\320\263\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        pushButton->setText(QApplication::translate("randomEntryWindow", "\320\241\320\263\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class randomEntryWindow: public Ui_randomEntryWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANDOMENTRYWINDOW_H
