/********************************************************************************
** Form generated from reading UI file 'qttoysclass.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTTOYSCLASS_H
#define UI_QTTOYSCLASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtToysClass
{
public:
    QLabel *label;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *amountBt_2;
    QPushButton *closeBtn;
    QPushButton *t2sBt;
    QPushButton *upperBt;
    QPushButton *amountBt;
    QPushButton *s2tBt;
    QPushButton *lowerBt;
    QLabel *label_2;

    void setupUi(QWidget *QtToysClass)
    {
        if (QtToysClass->objectName().isEmpty())
            QtToysClass->setObjectName(QString::fromUtf8("QtToysClass"));
        QtToysClass->resize(475, 365);
        label = new QLabel(QtToysClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(9, 9, 421, 41));
        gridLayoutWidget = new QWidget(QtToysClass);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 70, 344, 201));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        amountBt_2 = new QPushButton(gridLayoutWidget);
        amountBt_2->setObjectName(QString::fromUtf8("amountBt_2"));
        amountBt_2->setEnabled(false);

        gridLayout->addWidget(amountBt_2, 0, 3, 1, 1);

        closeBtn = new QPushButton(gridLayoutWidget);
        closeBtn->setObjectName(QString::fromUtf8("closeBtn"));

        gridLayout->addWidget(closeBtn, 1, 2, 1, 1);

        t2sBt = new QPushButton(gridLayoutWidget);
        t2sBt->setObjectName(QString::fromUtf8("t2sBt"));

        gridLayout->addWidget(t2sBt, 1, 1, 1, 1);

        upperBt = new QPushButton(gridLayoutWidget);
        upperBt->setObjectName(QString::fromUtf8("upperBt"));

        gridLayout->addWidget(upperBt, 0, 0, 1, 1);

        amountBt = new QPushButton(gridLayoutWidget);
        amountBt->setObjectName(QString::fromUtf8("amountBt"));

        gridLayout->addWidget(amountBt, 0, 2, 1, 1);

        s2tBt = new QPushButton(gridLayoutWidget);
        s2tBt->setObjectName(QString::fromUtf8("s2tBt"));

        gridLayout->addWidget(s2tBt, 1, 0, 1, 1);

        lowerBt = new QPushButton(gridLayoutWidget);
        lowerBt->setObjectName(QString::fromUtf8("lowerBt"));

        gridLayout->addWidget(lowerBt, 0, 1, 1, 1);

        label_2 = new QLabel(QtToysClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 310, 131, 16));

        retranslateUi(QtToysClass);
        QObject::connect(upperBt, SIGNAL(clicked()), QtToysClass, SLOT(on_upper()));
        QObject::connect(lowerBt, SIGNAL(clicked()), QtToysClass, SLOT(on_lower()));
        QObject::connect(amountBt, SIGNAL(clicked()), QtToysClass, SLOT(on_amount()));
        QObject::connect(s2tBt, SIGNAL(clicked()), QtToysClass, SLOT(on_s2t()));
        QObject::connect(t2sBt, SIGNAL(clicked()), QtToysClass, SLOT(on_t2s()));

        QMetaObject::connectSlotsByName(QtToysClass);
    } // setupUi

    void retranslateUi(QWidget *QtToysClass)
    {
        QtToysClass->setWindowTitle(QCoreApplication::translate("QtToysClass", "QtTestClass", nullptr));
        label->setText(QCoreApplication::translate("QtToysClass", "notepad-- Toys\346\217\222\344\273\266\357\274\214\351\232\217\346\200\247\345\212\240\345\220\204\347\247\215\347\216\251\345\205\267\345\212\237\350\203\275\357\274\214\347\234\213\345\244\247\345\256\266\345\217\215\351\246\210\346\212\275\345\217\226\345\207\272\345\256\236\347\224\250\345\267\245\345\205\267\346\217\222\344\273\266", nullptr));
        amountBt_2->setText(QCoreApplication::translate("QtToysClass", "\350\275\254\345\210\260\346\225\260\345\255\227\351\207\221\351\242\235", nullptr));
        closeBtn->setText(QCoreApplication::translate("QtToysClass", "\345\205\263\351\227\255", nullptr));
        t2sBt->setText(QCoreApplication::translate("QtToysClass", "\347\271\201\344\275\223\350\275\254\347\256\200\344\275\223", nullptr));
        upperBt->setText(QCoreApplication::translate("QtToysClass", "\350\275\254\345\210\260\345\244\247\345\206\231", nullptr));
        amountBt->setText(QCoreApplication::translate("QtToysClass", "\350\275\254\345\210\260\345\244\247\345\206\231\351\207\221\351\242\235", nullptr));
        s2tBt->setText(QCoreApplication::translate("QtToysClass", "\347\256\200\344\275\223\350\275\254\347\271\201\344\275\223", nullptr));
        lowerBt->setText(QCoreApplication::translate("QtToysClass", "\350\275\254\345\210\260\345\260\217\345\206\231", nullptr));
        label_2->setText(QCoreApplication::translate("QtToysClass", "\345\275\223\345\211\215\344\273\205\346\224\257\346\214\201UTF-8\347\274\226\347\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtToysClass: public Ui_QtToysClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTTOYSCLASS_H
