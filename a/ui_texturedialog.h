/********************************************************************************
** Form generated from reading UI file 'texturedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTUREDIALOG_H
#define UI_TEXTUREDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TextureDialog
{
public:
    QPushButton *concelBtn;
    QPushButton *confirmBtn;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *pushButton;

    void setupUi(QWidget *TextureDialog)
    {
        if (TextureDialog->objectName().isEmpty())
            TextureDialog->setObjectName(QStringLiteral("TextureDialog"));
        TextureDialog->resize(445, 319);
        concelBtn = new QPushButton(TextureDialog);
        concelBtn->setObjectName(QStringLiteral("concelBtn"));
        concelBtn->setGeometry(QRect(280, 270, 75, 23));
        confirmBtn = new QPushButton(TextureDialog);
        confirmBtn->setObjectName(QStringLiteral("confirmBtn"));
        confirmBtn->setGeometry(QRect(160, 270, 75, 23));
        scrollArea = new QScrollArea(TextureDialog);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(20, 30, 411, 211));
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 409, 400));
//        scrollAreaWidgetContents->setContentsMargins(200,200,200,200);
//        scrollAreaWidgetContents->setMaximumHeight(20);
        scrollArea->setWidget(scrollAreaWidgetContents);
        pushButton = new QPushButton(TextureDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(40, 270, 75, 23));

        retranslateUi(TextureDialog);

        QMetaObject::connectSlotsByName(TextureDialog);
    } // setupUi

    void retranslateUi(QWidget *TextureDialog)
    {

        concelBtn->setText(QApplication::translate("TextureDialog", "\345\217\226\346\266\210", 0));
        confirmBtn->setText(QApplication::translate("TextureDialog", "\347\241\256\345\256\232", 0));
        pushButton->setText(QApplication::translate("TextureDialog", "\346\267\273\345\212\240", 0));
    } // retranslateUi

};

namespace Ui {
    class TextureDialog: public Ui_TextureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTUREDIALOG_H
