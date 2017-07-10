/********************************************************************************
** Form generated from reading UI file 'namedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NAMEDIALOG_H
#define UI_NAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NameDialog
{
public:
    QLabel *label;
    QLineEdit *name;
    QPushButton *confirmBtn;
    QPushButton *concelBtn;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QCheckBox *Pix;
    QCheckBox *Well;
    QCheckBox *Profile;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *fileRouteEdit;
    QPushButton *browseBtn;

    void setupUi(QDialog *NameDialog)
    {
        if (NameDialog->objectName().isEmpty())
            NameDialog->setObjectName(QStringLiteral("NameDialog"));
        NameDialog->setEnabled(true);
        NameDialog->resize(441, 362);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NameDialog->sizePolicy().hasHeightForWidth());
        NameDialog->setSizePolicy(sizePolicy);
        NameDialog->setSizeGripEnabled(false);
        label = new QLabel(NameDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 30, 221, 41));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        label->setFont(font);
        name = new QLineEdit(NameDialog);
        name->setObjectName(QStringLiteral("name"));
        name->setGeometry(QRect(150, 40, 181, 21));
        confirmBtn = new QPushButton(NameDialog);
        confirmBtn->setObjectName(QStringLiteral("confirmBtn"));
        confirmBtn->setGeometry(QRect(190, 280, 75, 23));
        concelBtn = new QPushButton(NameDialog);
        concelBtn->setObjectName(QStringLiteral("concelBtn"));
        concelBtn->setGeometry(QRect(300, 280, 75, 23));
        verticalLayoutWidget = new QWidget(NameDialog);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(160, 80, 161, 131));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Pix = new QCheckBox(verticalLayoutWidget);
        Pix->setObjectName(QStringLiteral("Pix"));

        verticalLayout->addWidget(Pix);

        Well = new QCheckBox(verticalLayoutWidget);
        Well->setObjectName(QStringLiteral("Well"));

        verticalLayout->addWidget(Well);

        Profile = new QCheckBox(verticalLayoutWidget);
        Profile->setObjectName(QStringLiteral("Profile"));

        verticalLayout->addWidget(Profile);

        label_2 = new QLabel(NameDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(70, 80, 81, 21));
        label_2->setFont(font);
        label_3 = new QLabel(NameDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(70, 240, 81, 21));
        label_3->setFont(font);
        fileRouteEdit = new QLineEdit(NameDialog);
        fileRouteEdit->setObjectName(QStringLiteral("fileRouteEdit"));
        fileRouteEdit->setGeometry(QRect(150, 240, 181, 21));
        browseBtn = new QPushButton(NameDialog);
        browseBtn->setObjectName(QStringLiteral("browseBtn"));
        browseBtn->setGeometry(QRect(340, 240, 71, 21));

        retranslateUi(NameDialog);

        QMetaObject::connectSlotsByName(NameDialog);
    } // setupUi

    void retranslateUi(QDialog *NameDialog)
    {
        NameDialog->setWindowTitle(QApplication::translate("NameDialog", "Dialog", 0));
        label->setText(QApplication::translate("NameDialog", "\351\241\271\347\233\256\345\220\215\347\247\260\357\274\232", 0));
        name->setText(QApplication::translate("NameDialog", "\345\255\244\344\270\234\345\274\200\345\217\221\347\216\260\347\212\266", 0));
        confirmBtn->setText(QApplication::translate("NameDialog", "\347\241\256\345\256\232", 0));
        concelBtn->setText(QApplication::translate("NameDialog", "\345\217\226\346\266\210", 0));
        Pix->setText(QApplication::translate("NameDialog", "Exploratory", 0));
        Well->setText(QApplication::translate("NameDialog", "Well", 0));
        Profile->setText(QApplication::translate("NameDialog", "Profile", 0));
        label_2->setText(QApplication::translate("NameDialog", "\351\241\271\347\233\256\345\206\205\345\256\271\357\274\232", 0));
        label_3->setText(QApplication::translate("NameDialog", "\351\241\271\347\233\256\350\267\257\345\276\204\357\274\232", 0));
        browseBtn->setText(QApplication::translate("NameDialog", "\346\265\217\350\247\210", 0));
    } // retranslateUi

};

namespace Ui {
    class NameDialog: public Ui_NameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NAMEDIALOG_H
