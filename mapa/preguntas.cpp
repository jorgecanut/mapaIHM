#include "preguntas.h"
#include "ui_preguntas.h"

Preguntas::Preguntas(User *user, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Preguntas)
    , m_user(user)
{
    ui->setupUi(this);
}

Preguntas::~Preguntas()
{
    delete ui;
}


