#include "login_register.h"
#include "ui_login_register.h"
#include "utils.h"
#include "mainwindow.h"
#include <QFile>
#include <QString>
#include <QFileDialog>

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
    connect(ui->label_3, &ClickableLabel::clicked, this,&LoginRegister::cambiarPag2);
    connect(ui->label_10, &ClickableLabel::clicked, this, &LoginRegister::cambiarPag1);

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
    connect(ui->pbConfirmar, &QPushButton::clicked, this, &LoginRegister::addUserButton);
    connect(ui->pbAvatarElegir, &QPushButton::clicked,this, &LoginRegister::seleccionAvatar);
    connect(ui->leUsuario_IS, &QLineEdit::textChanged,this, &LoginRegister::check_login_fields);
    connect(ui->leContrasea_IS, &QLineEdit::textChanged, this, &LoginRegister::check_login_fields);
    check_login_fields();

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
    updateRegisterAcceptEnabled();
}

void LoginRegister::manageCorrect(QLabel *errorLabel, QLineEdit *edit, bool &flag)
{
    flag = true;
    hideErrorMessage(errorLabel, edit);
    updateRegisterAcceptEnabled();
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
    if(nav.findUser(ui->leUsuario_IS->text())){
        if(nav.findUser(ui->leUsuario_IS->text())->password() == ui->leContrasea_IS->text()){
            MainWindow *ventanaPrincipal = new MainWindow();

            // 2. Mostrar la ventana principal
            ventanaPrincipal->show();

            // 3. Cerrar la ventana de Login actual
            this->close();
        }else{
            ui->lErrorContrasea_IS->setVisible(true);
        }
    }else{
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
            QPixmap avatar(":/iconos_usuarios/batman.svg");
            if(ui->lAvatar->pixmap().isNull()){
                ui->lAvatar->setFixedSize(128,128);
                ui->lAvatar->setScaledContents(true);
                ui->lAvatar->setPixmap(avatar);

                ui->lAvatar->update();
            }
            User u(ui->leUsuario->text(),
                   ui->leEmail->text(),
                   ui->leContrasea->text(),
                   ui->lAvatar->pixmap().toImage(),
                   ui->dateEdit->date());
            nav.addUser(u);

            MainWindow *ventanaPrincipal = new MainWindow();

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
void LoginRegister::seleccionAvatar(){
    QString fileName = QFileDialog::getOpenFileName(this, "Seleccionar avatar", QDir::homePath(), "Imagenes:(*.png *.jpg *.jpeg *.bmp *.svg *.avif)");

    if(fileName.isEmpty()) return;

    QPixmap avatar(fileName);
    if(avatar.isNull()){
        qDebug() << "No se pudo cargar: " << fileName;
        return;
    }
    ui->lAvatar->setFixedSize(128,128);
    ui->lAvatar->setScaledContents(true);
    ui->lAvatar->setPixmap(avatar);

    ui->lAvatar->update();
}
void LoginRegister::cambiarPag1()
{
    // 1. Limpiar campos del formulario de LOGIN
    ui->leUsuario_IS->clear();
    ui->leContrasea_IS->clear();
    ui->lErrorEmail->setVisible(false);
    ui->lErrorPassword->setVisible(false);
    ui->lErrorRepPassword->setVisible(false);
    ui->lErrorNombreUsuario->setVisible(false);
    QPixmap emptyPixmap;
    ui->lAvatar->setPixmap(emptyPixmap);
    ui->stackedWidget->setCurrentIndex(1);
}
void LoginRegister::cambiarPag2()
{
    // 1. Limpiar campos del formulario de REGISTRO
    ui->leUsuario->clear();
    ui->leEmail->clear();
    ui->leContrasea->clear();
    ui->leRepContrasea->clear();
    ui->lErrorUsuario_IS->setVisible(false);
    ui->lErrorContrasea_IS->setVisible(false);
    ui->stackedWidget->setCurrentIndex(0);
}
void LoginRegister::check_login_fields()
{
    bool camposLlenos = !ui->leUsuario_IS->text().isEmpty() &&
                        !ui->leContrasea_IS->text().isEmpty();

    ui->pbInicioSesion->setEnabled(camposLlenos);
}

void LoginRegister::check_register_fields()
{
    bool camposLlenos = !ui->leUsuario->text().isEmpty() &&
                        !ui->leEmail->text().isEmpty() &&
                        !ui->leContrasea->text().isEmpty() &&
                        !ui->leRepContrasea->text().isEmpty();

    ui->pbConfirmar->setEnabled(camposLlenos);
}
void LoginRegister::updateRegisterAcceptEnabled()
{
    // Criterio de validación estricto: TODOS deben ser válidos Y no vacíos.
    bool allValid = validEmail && validPassword && validUsername && validRepPassword &&
                    !ui->leUsuario->text().isEmpty() &&
                    !ui->leEmail->text().isEmpty() &&
                    !ui->leContrasea->text().isEmpty() &&
                    !ui->leRepContrasea->text().isEmpty();

    ui->pbConfirmar->setEnabled(allValid);
}

// (Tu función original, renombrada para mayor claridad)
void LoginRegister::updateLoginAcceptEnabled()
{
    bool allValid = validEmail && validPassword && validUsername && validRepPassword;
    ui->pbInicioSesion->setEnabled(allValid);
}

// **Nota:** No modifiques check_register_fields() todavía, ya que ahora es redundante.
