#include "login_register.h"
#include "ui_login_register.h"
#include "utils.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

LoginRegister::LoginRegister(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginRegister)
    , validEmail(false)
    , validPassword(false)
{
    ui->setupUi(this);

    ui->lErrorEmail->setVisible(false);
    ui->lErrorPassword->setVisible(false);
    ui->lErrorRepPassword->setVisible(false);

    // Conecta el click de label_3 para cambiar de página
    connect(ui->label_3, &ClickableLabel::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->page);


    });
    connect(ui->label_10, &ClickableLabel::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->page_2);


    });
    connect(ui->checkBox_2, &QCheckBox::toggled, this, [this](bool checked) {
        if (checked) {
            ui->lineEdit_6->setEchoMode(QLineEdit::Normal);
        } else {
            ui->lineEdit_6->setEchoMode(QLineEdit::Password);
        }
    });
    connect(ui->checkContraseaRegister, &QCheckBox::toggled, this, [this](bool checked) {
        if (checked) {
            ui->leContrasea->setEchoMode(QLineEdit::Normal);
        } else {
            ui->leContrasea->setEchoMode(QLineEdit::Password);
        }
    });
    connect(ui->checkContraseaEqualRegister, &QCheckBox::toggled, this, [this](bool checked) {
        if (checked) {
            ui->leRepContrasea->setEchoMode(QLineEdit::Normal);
        } else {
            ui->leRepContrasea->setEchoMode(QLineEdit::Password);
        }
    });

    //
    connect(ui->leEmail, &QLineEdit::editingFinished,this, &LoginRegister::onEmailEditingFinished);
    connect(ui->leContrasea, &QLineEdit::editingFinished, this, &LoginRegister::checkPassword);
    connect(ui->leRepContrasea, &QLineEdit::editingFinished, this, &LoginRegister::checkEqualPassword);

//
}

LoginRegister::~LoginRegister()
{
    delete ui;
}
void LoginRegister::manageError(QLabel *errorLabel, QLineEdit *edit, bool &flag)
{
    flag = false;
    showErrorMessage(errorLabel, edit);
    edit->setFocus();
    updateAcceptEnabled();
}

void LoginRegister::manageCorrect(QLabel *errorLabel, QLineEdit *edit, bool &flag)
{
    flag = true;
    hideErrorMessage(errorLabel, edit);
    updateAcceptEnabled();
}

void LoginRegister::showErrorMessage(QLabel *errorLabel, QLineEdit *edit)
{
    if (errorLabel) {
        errorLabel->setVisible(true);
    }
    if (edit) {
        edit->setStyleSheet("background-color: #FCE5E0;");
    }
}

void LoginRegister::hideErrorMessage(QLabel *errorLabel, QLineEdit *edit)
{
    if (errorLabel) {
        errorLabel->setVisible(false);
    }
    if (edit) {
        edit->setStyleSheet("");
    }
}

// ======= Validaciones =======

void LoginRegister::checkEmail()
{
    const QString value = ui->leEmail->text();

    if (!Utils::checkEmail(value)) {
        manageError(ui->lErrorEmail, ui->leEmail, validEmail);
    } else {
        manageCorrect(ui->lErrorEmail, ui->leEmail, validEmail);
    }
}

void LoginRegister::checkPassword()
{
    const QString value = ui->leContrasea->text();

    if(!Utils::checkPassword(value)){
        manageError(ui->lErrorPassword,ui->leContrasea, validPassword);
    } else {
        manageCorrect(ui->lErrorPassword,ui->leContrasea,validPassword);
    }
}

void LoginRegister::checkEqualPassword(){
    const QString value_1 = ui->leContrasea->text();
    const QString value_2 = ui->leRepContrasea-> text();

    if(!Utils::checkRepPassword(value_2, value_1)){
        manageError(ui->lErrorRepPassword, ui->leRepContrasea, validRepPassword);
    }else{
        manageCorrect(ui->lErrorRepPassword, ui->leRepContrasea, validRepPassword);
    }
}

// ======= Slots de edición finalizada =======

void LoginRegister::onEmailEditingFinished()
{
    checkEmail();
}





// ======= Botones =======





// ======= Habilitar / deshabilitar botón Aceptar =======

void LoginRegister::updateAcceptEnabled()
{
    bool allValid = validEmail && validPassword;
    ui->pushButton_2->setEnabled(allValid);
}

