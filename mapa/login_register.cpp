#include "login_register.h"
#include "ui_login_register.h"
#include "utils.h"
#include "mainwindow.h"
#include <QFile>
#include <QString>
#include <QFileDialog>
#include <QKeyEvent>

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
    configurarAvatar();
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

void LoginRegister::checkUserName() {
    Navigation &nav = Navigation::instance();
    QString nombreUsuario = ui->leUsuario->text();

    // 1. Primero comprobamos si el formato es correcto (6-15 caracteres, etc.)
    bool formatoValido = Utils::checkUsuario(nombreUsuario);

    if (!formatoValido) {
        validUsername = false;
        ui->lErrorNombreUsuario->setText("Usuario inválido (6-15 caracteres, sin espacios)");
        ui->lErrorNombreUsuario->setVisible(true);
        ui->leUsuario->setFocus();
        return; // Salimos de la función si el formato ya está mal
    }

    // 2. Si el formato es correcto, comprobamos si ya existe en el sistema
    if (!nav.findUser(nombreUsuario)) {
        validUsername = true;
        ui->lErrorNombreUsuario->setVisible(false);
    } else {
        validUsername = false;
        ui->lErrorNombreUsuario->setText("El nombre de usuario ya está en uso");
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
            ventanaPrincipal->showMaximized();

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

            User *user = nav.findUser(ui->leUsuario->text());
            MainWindow *ventanaPrincipal = new MainWindow(user);

            // 2. Mostrar la ventana principal
            ventanaPrincipal->showMaximized();

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

void LoginRegister::updateLoginAcceptEnabled()
{
    bool allValid = validEmail && validPassword && validUsername && validRepPassword;
    ui->pbInicioSesion->setEnabled(allValid);
}


void LoginRegister::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        int currentPageIndex = ui->stackedWidget->currentIndex();

        if (currentPageIndex == 0) {
            if (ui->pbInicioSesion->isEnabled()) {
                emit ui->pbInicioSesion->clicked();
                return;
            }
        } else if (currentPageIndex == 1) {
            if (ui->pbConfirmar->isEnabled()) {
                emit ui->pbConfirmar->clicked();
                return; // Consumir el evento
            }
        }
    }
    QMainWindow::keyPressEvent(event);
}
void LoginRegister::configurarAvatar()
{
    if (!ui->lAvatar || !ui->pbAvatarElegir) return;

    // Según el XML que me pasaste, el avatar mide 128x128
    const int avatarSize = 128;
    const int avatarX = 5;
    const int avatarY = 5;

    // AL SUBIR EL OFFSET, EL BOTÓN SE METE HACIA EL CENTRO
    // Prueba con 45 para que esté bien encima de la imagen
    const int offset = 45;

    // Calculamos la posición
    int newX = avatarX + avatarSize - offset;
    int newY = avatarY + avatarSize - offset;

    // Mover y asegurar que esté al frente
    ui->pbAvatarElegir->move(newX, newY);
    ui->pbAvatarElegir->raise();
}
void LoginRegister::resizeEvent(QResizeEvent *event)
{
    // Llama a la implementación base para que la QMainWindow gestione sus layouts
    QMainWindow::resizeEvent(event);

    // Recalcula la posición del botón de edición
    configurarAvatar();
}
