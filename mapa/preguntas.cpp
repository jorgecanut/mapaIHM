#include "preguntas.h"
#include "ui_preguntas.h"

Preguntas::Preguntas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Preguntas)
{
    ui->setupUi(this);
}

Preguntas::~Preguntas()
{
    delete ui;
}
