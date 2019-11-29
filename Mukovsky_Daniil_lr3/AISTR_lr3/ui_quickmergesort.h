/********************************************************************************
** Form generated from reading UI file 'quickmergesort.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUICKMERGESORT_H
#define UI_QUICKMERGESORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QuickMergeSort
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextBrowser *input;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *comboBox;
    QPushButton *buttonQMergeSort;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QPushButton *pushButton;
    QTextBrowser *resultText;
    QLabel *labelSave;
    QLineEdit *lineSave;
    QPushButton *save;

    void setupUi(QDialog *QuickMergeSort)
    {
        if (QuickMergeSort->objectName().isEmpty())
            QuickMergeSort->setObjectName(QString::fromUtf8("QuickMergeSort"));
        QuickMergeSort->resize(1022, 941);
        QuickMergeSort->setMinimumSize(QSize(1022, 941));
        verticalLayout = new QVBoxLayout(QuickMergeSort);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(QuickMergeSort);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        input = new QTextBrowser(QuickMergeSort);
        input->setObjectName(QString::fromUtf8("input"));
        input->setMinimumSize(QSize(0, 100));
        input->setMaximumSize(QSize(16777215, 100));

        verticalLayout->addWidget(input);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(QuickMergeSort);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBox = new QComboBox(QuickMergeSort);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout);

        buttonQMergeSort = new QPushButton(QuickMergeSort);
        buttonQMergeSort->setObjectName(QString::fromUtf8("buttonQMergeSort"));

        verticalLayout->addWidget(buttonQMergeSort, 0, Qt::AlignRight);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(QuickMergeSort);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        pushButton = new QPushButton(QuickMergeSort);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_2);

        resultText = new QTextBrowser(QuickMergeSort);
        resultText->setObjectName(QString::fromUtf8("resultText"));
        resultText->setMinimumSize(QSize(1000, 600));

        verticalLayout->addWidget(resultText);

        labelSave = new QLabel(QuickMergeSort);
        labelSave->setObjectName(QString::fromUtf8("labelSave"));

        verticalLayout->addWidget(labelSave);

        lineSave = new QLineEdit(QuickMergeSort);
        lineSave->setObjectName(QString::fromUtf8("lineSave"));

        verticalLayout->addWidget(lineSave);

        save = new QPushButton(QuickMergeSort);
        save->setObjectName(QString::fromUtf8("save"));

        verticalLayout->addWidget(save, 0, Qt::AlignRight);


        retranslateUi(QuickMergeSort);

        QMetaObject::connectSlotsByName(QuickMergeSort);
    } // setupUi

    void retranslateUi(QDialog *QuickMergeSort)
    {
        QuickMergeSort->setWindowTitle(QApplication::translate("QuickMergeSort", "Dialog", nullptr));
        label->setText(QApplication::translate("QuickMergeSort", "\320\230\321\201\321\205\320\276\320\264\320\275\321\213\320\271 \320\274\320\260\321\201\321\201\320\270\320\262", nullptr));
        label_2->setText(QApplication::translate("QuickMergeSort", "\320\222\321\213\320\261\320\265\321\200\320\265\321\202\320\265 \321\200\320\265\320\266\320\270\320\274 \321\201\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\272\320\270", nullptr));
        buttonQMergeSort->setText(QApplication::translate("QuickMergeSort", "\320\236\321\202\321\201\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        label_3->setText(QApplication::translate("QuickMergeSort", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202:", nullptr));
        pushButton->setText(QApplication::translate("QuickMergeSort", "\320\241\320\273\320\265\320\264\321\203\321\216\321\211\320\270\320\271 \320\250\320\260\320\263", nullptr));
        labelSave->setText(QApplication::translate("QuickMergeSort", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\321\203\321\202\321\214 \320\272 \321\202\320\265\320\272\321\201\321\202\320\276\320\262\320\276\320\274\321\203 \321\204\320\260\320\271\320\273\321\203, \320\262 \320\272\320\276\321\202\320\276\321\200\320\276\320\274 \321\205\320\276\321\202\320\270\321\202\320\265 \321\201\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202", nullptr));
        save->setText(QApplication::translate("QuickMergeSort", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QuickMergeSort: public Ui_QuickMergeSort {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUICKMERGESORT_H
