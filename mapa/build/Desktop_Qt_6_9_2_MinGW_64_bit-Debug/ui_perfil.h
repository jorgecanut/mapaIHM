/********************************************************************************
** Form generated from reading UI file 'perfil.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERFIL_H
#define UI_PERFIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Perfil
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer;
    QTextEdit *textEdit;
    QLabel *label_3;
    QTextEdit *textEdit_2;
    QLabel *label_4;
    QTextEdit *textEdit_3;
    QLabel *label_5;
    QDateEdit *dateEdit;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Perfil)
    {
        if (Perfil->objectName().isEmpty())
            Perfil->setObjectName("Perfil");
        Perfil->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Perfil->sizePolicy().hasHeightForWidth());
        Perfil->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(Perfil);
        centralwidget->setObjectName("centralwidget");
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(0, 550));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        label->setFont(font);
        label->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName("comboBox");
        comboBox->setMinimumSize(QSize(0, 100));
        comboBox->setMaximumSize(QSize(200, 300));

        verticalLayout->addWidget(comboBox);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Ignored);

        verticalLayout->addItem(verticalSpacer);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setMaximumSize(QSize(300, 30));

        verticalLayout->addWidget(textEdit);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        textEdit_2 = new QTextEdit(centralwidget);
        textEdit_2->setObjectName("textEdit_2");
        textEdit_2->setMaximumSize(QSize(300, 30));

        verticalLayout->addWidget(textEdit_2);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        textEdit_3 = new QTextEdit(centralwidget);
        textEdit_3->setObjectName("textEdit_3");
        textEdit_3->setMaximumSize(QSize(400, 30));

        verticalLayout->addWidget(textEdit_3);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        verticalLayout->addWidget(label_5);

        dateEdit = new QDateEdit(centralwidget);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(dateEdit);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setMaximumSize(QSize(200, 16777215));
        pushButton->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        verticalLayout->addWidget(pushButton);

        Perfil->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Perfil);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        Perfil->setMenuBar(menubar);
        statusbar = new QStatusBar(Perfil);
        statusbar->setObjectName("statusbar");
        Perfil->setStatusBar(statusbar);

        retranslateUi(Perfil);

        QMetaObject::connectSlotsByName(Perfil);
    } // setupUi

    void retranslateUi(QMainWindow *Perfil)
    {
        Perfil->setWindowTitle(QCoreApplication::translate("Perfil", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("Perfil", "DATOS PERFIL", nullptr));
        label_2->setText(QCoreApplication::translate("Perfil", "Nombre de usuario", nullptr));
        label_3->setText(QCoreApplication::translate("Perfil", "Contrase\303\261a", nullptr));
        label_4->setText(QCoreApplication::translate("Perfil", "Correo electr\303\263nico", nullptr));
        label_5->setText(QCoreApplication::translate("Perfil", "Fecha de nacimiento", nullptr));
        pushButton->setText(QCoreApplication::translate("Perfil", "CONFIRMAR CAMBIOS", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Perfil: public Ui_Perfil {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERFIL_H
