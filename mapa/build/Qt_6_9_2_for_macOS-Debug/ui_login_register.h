/********************************************************************************
** Form generated from reading UI file 'login_register.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_REGISTER_H
#define UI_LOGIN_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <login_register.h>

QT_BEGIN_NAMESPACE

class Ui_LoginRegister
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_11;
    QSpacerItem *verticalSpacer_8;
    QLabel *label_9;
    QLineEdit *lineEdit_4;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_8;
    QLineEdit *lineEdit_6;
    ClickableLabel *label_12;
    QCheckBox *checkBox_2;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer_3;
    ClickableLabel *label_10;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_2;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_7;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_6;
    QLineEdit *leUsuario;
    QSpacerItem *verticalSpacer;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *leEmail;
    QLabel *lErrorEmail;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *leContrasea;
    QLabel *lErrorPassword;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *checkContraseaRegister;
    QSpacerItem *verticalSpacer_9;
    QLabel *label_2;
    QDateEdit *dateEdit;
    QLabel *label;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    ClickableLabel *label_3;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_13;
    QLabel *label_14;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LoginRegister)
    {
        if (LoginRegister->objectName().isEmpty())
            LoginRegister->setObjectName("LoginRegister");
        LoginRegister->resize(794, 555);
        LoginRegister->setMaximumSize(QSize(16777215, 555));
        centralwidget = new QWidget(LoginRegister);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setMaximumSize(QSize(16777215, 500));
        page = new QWidget();
        page->setObjectName("page");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(page->sizePolicy().hasHeightForWidth());
        page->setSizePolicy(sizePolicy);
        page->setStyleSheet(QString::fromUtf8(""));
        verticalLayoutWidget = new QWidget(page);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 30, 751, 511));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(12, 12, 12, 0);
        label_11 = new QLabel(verticalLayoutWidget);
        label_11->setObjectName("label_11");
        QFont font;
        font.setPointSize(20);
        label_11->setFont(font);
        label_11->setScaledContents(true);
        label_11->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label_11);

        verticalSpacer_8 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_8);

        label_9 = new QLabel(verticalLayoutWidget);
        label_9->setObjectName("label_9");
        label_9->setMaximumSize(QSize(16777215, 41));

        verticalLayout_3->addWidget(label_9);

        lineEdit_4 = new QLineEdit(verticalLayoutWidget);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setMaximumSize(QSize(300, 16777215));
        lineEdit_4->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_3->addWidget(lineEdit_4);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_7);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_8 = new QLabel(verticalLayoutWidget);
        label_8->setObjectName("label_8");
        label_8->setMaximumSize(QSize(16777215, 37));

        verticalLayout_5->addWidget(label_8);

        lineEdit_6 = new QLineEdit(verticalLayoutWidget);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setMaximumSize(QSize(300, 16777215));
        lineEdit_6->setEchoMode(QLineEdit::EchoMode::Password);
        lineEdit_6->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_5->addWidget(lineEdit_6);

        label_12 = new ClickableLabel(verticalLayoutWidget);
        label_12->setObjectName("label_12");
        label_12->setStyleSheet(QString::fromUtf8("color: #0066cc;\n"
"}\n"
"ClickableLabel:hover {\n"
"    color: #004999;\n"
"}\n"
""));
        label_12->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_5->addWidget(label_12);


        horizontalLayout_4->addLayout(verticalLayout_5);

        checkBox_2 = new QCheckBox(verticalLayoutWidget);
        checkBox_2->setObjectName("checkBox_2");
        checkBox_2->setMaximumSize(QSize(500, 16777215));

        horizontalLayout_4->addWidget(checkBox_2);


        verticalLayout_3->addLayout(horizontalLayout_4);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        checkBox = new QCheckBox(verticalLayoutWidget);
        checkBox->setObjectName("checkBox");

        horizontalLayout_2->addWidget(checkBox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_10 = new ClickableLabel(verticalLayoutWidget);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("color: #0066cc;\n"
"}\n"
"ClickableLabel:hover {\n"
"    color: #004999;\n"
"}\n"
""));
        label_10->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(label_10);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(0, 50));
        pushButton_2->setMaximumSize(QSize(200, 300));
        QFont font1;
        font1.setBold(true);
        pushButton_2->setFont(font1);

        horizontalLayout_3->addWidget(pushButton_2);


        verticalLayout_3->addLayout(horizontalLayout_3);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        page_2->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(page_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        verticalLayout->setContentsMargins(12, 12, 12, 12);
        label_7 = new QLabel(page_2);
        label_7->setObjectName("label_7");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setPointSize(20);
        font2.setBold(true);
        font2.setUnderline(false);
        label_7->setFont(font2);
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_7);

        verticalSpacer_5 = new QSpacerItem(17, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        label_6 = new QLabel(page_2);
        label_6->setObjectName("label_6");

        verticalLayout->addWidget(label_6);

        leUsuario = new QLineEdit(page_2);
        leUsuario->setObjectName("leUsuario");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(leUsuario->sizePolicy().hasHeightForWidth());
        leUsuario->setSizePolicy(sizePolicy2);
        leUsuario->setMinimumSize(QSize(300, 0));
        leUsuario->setMaximumSize(QSize(300, 16777215));

        verticalLayout->addWidget(leUsuario);

        verticalSpacer = new QSpacerItem(17, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_5 = new QLabel(page_2);
        label_5->setObjectName("label_5");

        verticalLayout->addWidget(label_5);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        leEmail = new QLineEdit(page_2);
        leEmail->setObjectName("leEmail");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(leEmail->sizePolicy().hasHeightForWidth());
        leEmail->setSizePolicy(sizePolicy3);
        leEmail->setMinimumSize(QSize(400, 0));
        leEmail->setMaximumSize(QSize(400, 16777215));

        horizontalLayout_5->addWidget(leEmail);

        lErrorEmail = new QLabel(page_2);
        lErrorEmail->setObjectName("lErrorEmail");
        lErrorEmail->setStyleSheet(QString::fromUtf8("color:red"));

        horizontalLayout_5->addWidget(lErrorEmail);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_2 = new QSpacerItem(17, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_4 = new QLabel(page_2);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        leContrasea = new QLineEdit(page_2);
        leContrasea->setObjectName("leContrasea");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(leContrasea->sizePolicy().hasHeightForWidth());
        leContrasea->setSizePolicy(sizePolicy4);
        leContrasea->setMinimumSize(QSize(300, 0));
        leContrasea->setMaximumSize(QSize(300, 16777215));
        leContrasea->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_6->addWidget(leContrasea);

        lErrorPassword = new QLabel(page_2);
        lErrorPassword->setObjectName("lErrorPassword");
        lErrorPassword->setStyleSheet(QString::fromUtf8("color:red"));

        horizontalLayout_6->addWidget(lErrorPassword);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_6);

        checkContraseaRegister = new QCheckBox(page_2);
        checkContraseaRegister->setObjectName("checkContraseaRegister");
        checkContraseaRegister->setAutoExclusive(false);

        verticalLayout->addWidget(checkContraseaRegister);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_9);

        label_2 = new QLabel(page_2);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        dateEdit = new QDateEdit(page_2);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setMinimumSize(QSize(200, 0));
        dateEdit->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(dateEdit);

        label = new QLabel(page_2);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        comboBox = new QComboBox(page_2);
        comboBox->setObjectName("comboBox");
        comboBox->setMinimumSize(QSize(0, 60));
        comboBox->setMaximumSize(QSize(100, 16777215));

        verticalLayout->addWidget(comboBox);

        verticalSpacer_4 = new QSpacerItem(17, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(page_2);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy5);
        pushButton->setMinimumSize(QSize(110, 50));
        pushButton->setMaximumSize(QSize(100, 16777215));
        pushButton->setFont(font1);

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        label_3 = new ClickableLabel(page_2);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("color: #0066cc;\n"
"}\n"
"ClickableLabel:hover {\n"
"    color: #004999;\n"
"}\n"
""));
        label_3->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout->addWidget(label_3);


        verticalLayout_2->addLayout(verticalLayout);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        page_3->setMaximumSize(QSize(16777215, 300));
        verticalLayout_4 = new QVBoxLayout(page_3);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_13 = new QLabel(page_3);
        label_13->setObjectName("label_13");
        label_13->setMaximumSize(QSize(800, 70));
        QFont font3;
        font3.setPointSize(20);
        font3.setBold(true);
        label_13->setFont(font3);
        label_13->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(label_13);

        label_14 = new QLabel(page_3);
        label_14->setObjectName("label_14");
        label_14->setMaximumSize(QSize(800, 30));

        verticalLayout_4->addWidget(label_14);

        textEdit = new QTextEdit(page_3);
        textEdit->setObjectName("textEdit");
        sizePolicy5.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy5);
        textEdit->setMaximumSize(QSize(16777215, 30));

        verticalLayout_4->addWidget(textEdit);

        stackedWidget->addWidget(page_3);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);

        LoginRegister->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LoginRegister);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 794, 37));
        LoginRegister->setMenuBar(menubar);
        statusbar = new QStatusBar(LoginRegister);
        statusbar->setObjectName("statusbar");
        LoginRegister->setStatusBar(statusbar);

        retranslateUi(LoginRegister);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(LoginRegister);
    } // setupUi

    void retranslateUi(QMainWindow *LoginRegister)
    {
        LoginRegister->setWindowTitle(QCoreApplication::translate("LoginRegister", "MainWindow", nullptr));
        label_11->setText(QCoreApplication::translate("LoginRegister", "Iniciar sesi\303\263n", nullptr));
        label_9->setText(QCoreApplication::translate("LoginRegister", "Usuario", nullptr));
        label_8->setText(QCoreApplication::translate("LoginRegister", "Contrase\303\261a", nullptr));
        label_12->setText(QCoreApplication::translate("LoginRegister", "\302\277Has olvidado la contrase\303\261a?", nullptr));
        checkBox_2->setText(QCoreApplication::translate("LoginRegister", "Mostrar contrase\303\261a", nullptr));
        checkBox->setText(QCoreApplication::translate("LoginRegister", "Recordar", nullptr));
        label_10->setText(QCoreApplication::translate("LoginRegister", "\302\277No tienes cuenta todav\303\255a?", nullptr));
        pushButton_2->setText(QCoreApplication::translate("LoginRegister", "Iniciar sesi\303\263n", nullptr));
        label_7->setText(QCoreApplication::translate("LoginRegister", "REGISTRARSE", nullptr));
        label_6->setText(QCoreApplication::translate("LoginRegister", "Usuario", nullptr));
        label_5->setText(QCoreApplication::translate("LoginRegister", "Correo electr\303\263nico", nullptr));
        lErrorEmail->setText(QCoreApplication::translate("LoginRegister", "El correo introducido no es correcto", nullptr));
        label_4->setText(QCoreApplication::translate("LoginRegister", "Contrase\303\261a", nullptr));
        lErrorPassword->setText(QCoreApplication::translate("LoginRegister", "La contrase\303\261a debe incluir caracteres especiales y num\303\251ricos", nullptr));
        checkContraseaRegister->setText(QCoreApplication::translate("LoginRegister", "Mostrar contrase\303\261a", nullptr));
        label_2->setText(QCoreApplication::translate("LoginRegister", "A\303\261o de nacimiento", nullptr));
        dateEdit->setDisplayFormat(QCoreApplication::translate("LoginRegister", "dd/MM/yyyy", nullptr));
        label->setText(QCoreApplication::translate("LoginRegister", "Avatar", nullptr));
        pushButton->setText(QCoreApplication::translate("LoginRegister", "CONFIRMAR", nullptr));
        label_3->setText(QCoreApplication::translate("LoginRegister", "\302\277Ya tienes cuenta?", nullptr));
        label_13->setText(QCoreApplication::translate("LoginRegister", "\302\277Quiere restablecer su contrase\303\261a?", nullptr));
        label_14->setText(QCoreApplication::translate("LoginRegister", "Introduzca su correo electr\303\263nico", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginRegister: public Ui_LoginRegister {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_REGISTER_H
