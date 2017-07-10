/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_3;
    QCheckBox *check;
    QLineEdit *name_1;
    QLabel *label_14;
    QLineEdit *name_2;
    QLabel *label_15;
    QLineEdit *name_3;
    QPushButton *choose;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(375, 86);
        layoutWidget_2 = new QWidget(Form);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 20, 350, 51));
        gridLayout_3 = new QGridLayout(layoutWidget_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        check = new QCheckBox(layoutWidget_2);
        check->setObjectName(QStringLiteral("check"));
        check->setChecked(false);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        check->setFont(font);

        gridLayout_3->addWidget(check, 0, 0, 1, 2);

        name_1 = new QLineEdit(layoutWidget_2);
        name_1->setObjectName(QStringLiteral("name_1"));
        name_1->setEnabled(false);
        gridLayout_3->addWidget(name_1, 0, 3, 1, 2);

        label_14 = new QLabel(layoutWidget_2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setFont(font);

        gridLayout_3->addWidget(label_14, 1, 0, 1, 1);

        name_2 = new QLineEdit(layoutWidget_2);
        name_2->setObjectName(QStringLiteral("name_2"));

        gridLayout_3->addWidget(name_2, 1, 1, 1, 2);

        label_15 = new QLabel(layoutWidget_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setFont(font);

        gridLayout_3->addWidget(label_15, 1, 3, 1, 1);

        name_3 = new QLineEdit(layoutWidget_2);
        name_3->setObjectName(QStringLiteral("name_3"));

        gridLayout_3->addWidget(name_3, 1, 4, 1, 1);

        choose = new QPushButton(layoutWidget_2);
        choose->setObjectName(QStringLiteral("choose"));

        gridLayout_3->addWidget(choose, 0, 2, 1, 1);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        check->setText(QApplication::translate("Form", "\350\264\264\345\233\276", 0));
        name_1->setText(QString());
        label_14->setText(QApplication::translate("Form", "\344\270\212\357\274\232", 0));
        name_2->setText(QString());
        label_15->setText(QApplication::translate("Form", "\344\270\213\357\274\232", 0));
        name_3->setText(QString());
        choose->setText(QApplication::translate("Form", "\345\233\276\347\211\207\351\200\211\346\213\251", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
