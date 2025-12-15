#include "perfil.h"
#include "ui_perfil.h"
#include "utils.h"

Perfil::Perfil(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Perfil)
    , validEmail(false)
    , validPassword(false)
    , validAge(false)
{
    ui->setupUi(this);

    QFile file(":/estilos/estilo.qss"); // Ruta al archivo en el recurso
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QString::fromUtf8(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }
    ui->lErrorCorreo->setVisible(false);
    ui->lErrorContrasea->setVisible(false);
    ui->lErrorFecha->setVisible(false);

    ui->leContrasea->setEchoMode(QLineEdit::Password);


    connect(ui->cMostrarContrasea, &QCheckBox::toggled, this, [this](bool checked) {
        if (checked) {
            ui->leContrasea->setEchoMode(QLineEdit::Normal);
        } else {
            ui->leContrasea->setEchoMode(QLineEdit::Password);
        }
    });

    connect(ui->leCorreo, &QLineEdit::editingFinished,this, &Perfil::onEmailEditingFinished);
    connect(ui->leContrasea, &QLineEdit::editingFinished, this, &Perfil::checkPassword);
    connect(ui->daFechaNacimiento, &QDateEdit::editingFinished, this, &Perfil::checkDate);

    connect(ui->pbCambiarAvatar, &QPushButton::clicked, this, &Perfil::seleccionAvatar);



    connect(ui->pbConfirmarCambios, &QPushButton::clicked, this, &Perfil::updateUserButton);
}
//TODO: Mostrar en todos los datos de la cuenta
//TODO: Resize de las pestañas
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
        edit->setStyleSheet("");
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

void Perfil::checkDate(){
    const QDate today_date = QDate::currentDate();
    const QDate date = ui->daFechaNacimiento->date();

    if(date.addYears(16) > today_date){
        validAge = false;
        ui->lErrorFecha->setVisible(true);
        ui->daFechaNacimiento->setFocus();
    }else{
        validAge = true;
        ui->lErrorFecha->setVisible(false);
    }
    updateAcceptEnabled();
}


// ======= Slots de edición finalizada =======

void Perfil::onEmailEditingFinished()
{
    checkEmail();
}

void Perfil::updateUserButton()
{
    try {
        Navigation &nav = Navigation::instance();
        if (nav.findUser(ui->leNombreUsuario->text())) {
            User u(ui->leNombreUsuario->text(),
                   ui->leCorreo->text(),
                   ui->leContrasea->text(),
                   ui->lAvatar->pixmap().toImage(),
                   ui->daFechaNacimiento->date());
            nav.updateUser(u);
            QMessageBox::information(this, "Información", "Información actualizada correctamente");
        }

    } catch (const NavDAOException &ex) {
        QMessageBox::critical(this, tr("DB error"), ex.what());
    }
}

// ======Cargar imagenes de la galeria=====
void Perfil::seleccionAvatar(){
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

// ======= Habilitar / deshabilitar botón Aceptar =======

void Perfil::updateAcceptEnabled()
{
    bool allValid = validEmail && validPassword && validAge;
    ui->pbConfirmarCambios->setEnabled(allValid);
}



