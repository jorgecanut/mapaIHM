#include "perfil.h"
#include "ui_perfil.h"

Perfil::Perfil(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Perfil)
{
    ui->setupUi(this);
}

Perfil::~Perfil()
{
    delete ui;
}
