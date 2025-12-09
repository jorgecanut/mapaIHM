#include "perfil.h"
#include "ui_perfil.h"
#include "utils.h"
#include "iconcombobox.h"

Perfil::Perfil(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Perfil)
    , validEmail(false)
    , validPassword(false)
{
    ui->setupUi(this);

    ui->lErrorCorreo->setVisible(false);
    ui->lErrorContrasea->setVisible(false);
    ui->lErrorNombreUsuario->setVisible(false);

    ui->cbAvatar->addIconItem(":/iconos_usuarios/aguacate.svg");
    ui->cbAvatar->addIconItem(":/iconos_usuarios/arana.svg");
    ui->cbAvatar->addIconItem(":/iconos_usuarios/batman.svg");
    ui->cbAvatar->addIconItem(":/iconos_usuarios/cactus.svg");
    ui->cbAvatar->addIconItem(":/iconos_usuarios/cafe.svg");
    ui->cbAvatar->addIconItem(":/iconos_usuarios/joker.svg");
    ui->cbAvatar->addIconItem(":/iconos_usuarios/oso.svg");
    ui->cbAvatar->addIconItem(":/iconos_usuarios/perezoso.svg");
    ui->cbAvatar->addIconItem(":/iconos_usuarios/vampiro.svg");
    ui->cbAvatar->addIconItem(":/iconos_usuarios/zombie.svg");
    ui->cbAvatar->setCurrentIndex(-1);

    connect(ui->cMostrarContrasea, &QCheckBox::toggled, this, [this](bool checked) {
        if (checked) {
            ui->leContrasea->setEchoMode(QLineEdit::Normal);
        } else {
            ui->leContrasea->setEchoMode(QLineEdit::Password);
        }
    });

    connect(ui->leCorreo, &QLineEdit::editingFinished,this, &Perfil::onEmailEditingFinished);
    connect(ui->leContrasea, &QLineEdit::editingFinished, this, &Perfil::checkPassword);
//TODO: funcion para comprobar que el usuario ya existe o no
    //connect(ui->leNombreUsuario, &QLineEdit::editingFinished, this, &Perfil::);
}

Perfil::~Perfil()
{
    delete ui;
}

void Perfil::manageError(QLabel *errorLabel, QLineEdit *edit, bool &flag)
{
    flag = false;
    showErrorMessage(errorLabel, edit);
    edit->setFocus();
    updateAcceptEnabled();
}

void Perfil::manageCorrect(QLabel *errorLabel, QLineEdit *edit, bool &flag)
{
    flag = true;
    hideErrorMessage(errorLabel, edit);
    updateAcceptEnabled();
}

void Perfil::showErrorMessage(QLabel *errorLabel, QLineEdit *edit)
{
    if (errorLabel) {
        errorLabel->setVisible(true);
    }
    if (edit) {
        edit->setStyleSheet("background-color: #FCE5E0;");
    }
}

void Perfil::hideErrorMessage(QLabel *errorLabel, QLineEdit *edit)
{
    if (errorLabel) {
        errorLabel->setVisible(false);
    }
    if (edit) {
        edit->setStyleSheet("");
    }
}

// ======= Validaciones =======

void Perfil::checkEmail()
{
    const QString value = ui->leCorreo->text();

    if (!Utils::checkEmail(value)) {
        manageError(ui->lErrorCorreo, ui->leCorreo, validEmail);
    } else {
        manageCorrect(ui->lErrorCorreo, ui->leCorreo, validEmail);
    }
}

void Perfil::checkPassword()
{
    const QString value = ui->leContrasea->text();

    if(!Utils::checkPassword(value)){
        manageError(ui->lErrorContrasea,ui->leContrasea, validPassword);
    } else {
        manageCorrect(ui->lErrorContrasea,ui->leContrasea,validPassword);
    }
}

// ======= Slots de edición finalizada =======

void Perfil::onEmailEditingFinished()
{
    checkEmail();
}


// ======= Habilitar / deshabilitar botón Aceptar =======

void Perfil::updateAcceptEnabled()
{
    bool allValid = validEmail && validPassword;
    ui->pbConfirmarCambios->setEnabled(allValid);
}
