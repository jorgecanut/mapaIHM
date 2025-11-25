#include "login_register.h"
#include "ui_login_register.h"


LoginRegister::LoginRegister(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginRegister)
    , validEmail(false)
    , validPassword(false)
    , equalPasswords(false)
{
    ui->setupUi(this);

    // Conecta el click de label_3 para cambiar de página
    connect(ui->label_3, &ClickableLabel::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->page);


    });
    connect(ui->label_10, &ClickableLabel::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->page_2);


    });
    connect(ui->checkBox_2, &QCheckBox::toggled, this, [this](bool checked) {
        if (checked) {
            ui->lePasswordLogin->setEchoMode(QLineEdit::Normal);
        } else {
            ui->lePasswordLogin->setEchoMode(QLineEdit::Password);
        }
    });
    connect(ui->checkBox_3, &QCheckBox::toggled, this, [this](bool checked) {
        if (checked) {
            ui->lePasswordRegister->setEchoMode(QLineEdit::Normal);
        } else {
            ui->lePasswordRegister->setEchoMode(QLineEdit::Password);
        }
    });

    connect(ui->label_12, &ClickableLabel::clicked, this, [this](){
        ui->stackedWidget->setCurrentWidget(ui->page_3);
    });

    // Para saber si has terminado de editar los campos (falta repetir contraseña en el register)
    connect(ui->leUserRegister, &QLineEdit::editingFinished,this, &LoginRegister::onUserEditingFinished);
    connect(ui->leMailRegister, &QLineEdit::editingFinished,this, &LoginRegister::onEmailEditingFinished);
    connect(ui->lePasswordRegister, &QLineEdit::editingFinished,this, &::LoginRegister::onPasswordEditingFinished);

    // En el login se debe poder introducir un mail también
    connect(ui->leUserLogin, &QLineEdit::editingFinished,this, &LoginRegister::onUserEditingFinished);
    connect(ui->lePasswordLogin, &QLineEdit::editingFinished,this, &::LoginRegister::onPasswordEditingFinished);

    // Botones (falta boton de cancelar)
    connect(ui->bConfirmarRegister, &QPushButton::clicked,this,&LoginRegister::onAcceptClicked);
    connect(ui->bAceptarLogin, &QPushButton::clicked,this,&LoginRegister::onAcceptClicked);
}

LoginRegister::~LoginRegister()
{
    delete ui;
}


void LoginRegister::onEmailEditingFinished()
{
    checkEmail();
    updateAcceptEnabled();
}

void LoginRegister::onPasswordEditingFinished()
{
    checkPassword();
    updateAcceptEnabled();
}

void LoginRegister::onUserEditingFinished()
{
    checkUser();
    updateAcceptEnabled();
}
