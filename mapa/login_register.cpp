#include "login_register.h"
#include "ui_login_register.h"
#include "utils.h"
#include "mainwindow.h"
#include <QFile>
#include <QString>

LoginRegister::LoginRegister(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginRegister)
    , validEmail(false)
    , validPassword(false)
    , validRepPassword(false)
    , validUsername(false)
{
    ui->setupUi(this);


    QFile file(":/estilos/estilo.qss"); // Ruta al archivo en el recurso
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QString::fromUtf8(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }

    ui->lErrorEmail->setVisible(false);
    ui->lErrorPassword->setVisible(false);
    ui->lErrorRepPassword->setVisible(false);
    ui->lErrorNombreUsuario->setVisible(false);
    ui->lErrorUsuario_IS->setVisible(false);
    ui->lErrorContrasea_IS->setVisible(false);

    // Conecta el click de label_3 para cambiar de página
    connect(ui->label_3, &ClickableLabel::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->page);


    });
    connect(ui->label_10, &ClickableLabel::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->page_2);


    });
    connect(ui->checkBox_2, &QCheckBox::toggled, this, [this](bool checked) {
        if (checked) {
            ui->leContrasea_IS->setEchoMode(QLineEdit::Normal);
        } else {
            ui->leContrasea_IS->setEchoMode(QLineEdit::Password);
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
    connect(ui->leUsuario, &QLineEdit::editingFinished, this, &LoginRegister::checkUserName);
    connect(ui->pbInicioSesion, &QPushButton::clicked, this, &LoginRegister::user_contr_correct);
    connect(ui->pushButton, &QPushButton::clicked, this, &LoginRegister::addUserButton);

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
        edit->setStyleSheet("");
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

void LoginRegister::checkUserName(){
    Navigation &nav = Navigation::instance();
    if(!nav.findUser(ui->leUsuario->text())){
        validUsername = true;
        ui->lErrorNombreUsuario->setVisible(false);
    }else{
        validUsername = false;
        ui->lErrorNombreUsuario->setVisible(true);
        ui->leUsuario->setFocus();
    }
}

void LoginRegister::user_contr_correct(){
    Navigation &nav = Navigation::instance();
    User *user = nav.authenticate(
        ui->leUsuario_IS->text(),
        ui->leContrasea_IS->text()
        );
    if(user){
            MainWindow *ventanaPrincipal = new MainWindow(user);

            // 2. Mostrar la ventana principal
            ventanaPrincipal->show();

            // 3. Cerrar la ventana de Login actual
            this->close();
    }else{
         ui->lErrorContrasea_IS->setVisible(true);
            ui->lErrorUsuario_IS->setVisible(true);
    }
}

// ======= Slots de edición finalizada =======

void LoginRegister::onEmailEditingFinished()
{
    checkEmail();
}





// ======= Botones =======



// ======= Añadir Usuario en Base de Datos =======
void LoginRegister::addUserButton()
{
    try {
        Navigation &nav = Navigation::instance();

        // Crear usuario si no existe
        if (!nav.findUser(ui->leUsuario->text())) {
            User u(ui->leUsuario->text(),
                   ui->leEmail->text(),
                   ui->leContrasea->text(),
                   QImage("zombie.svg"),
                   ui->dateEdit->date());
            nav.addUser(u);

            User *user = nav.findUser(ui->leUsuario->text());
            MainWindow *ventanaPrincipal = new MainWindow(user);

            // 2. Mostrar la ventana principal
            ventanaPrincipal->show();

            // 3. Cerrar la ventana de Login actual
            this->close();
        }



    } catch (const NavDAOException &ex) {
        QMessageBox::critical(this, tr("DB error"), ex.what());
    }
}

// ======= Habilitar / deshabilitar botón Aceptar =======

void LoginRegister::updateAcceptEnabled()
{
    bool allValid = validEmail && validPassword && validUsername && validRepPassword;
    ui->pbInicioSesion->setEnabled(allValid);
}
void LoginRegister::mostrarLogin()
{
    ui->stackedWidget->setCurrentIndex(0);
}

