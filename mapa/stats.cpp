#include "stats.h"
#include "ui_stats.h"

stats::stats(User *user,Session *sesion, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::stats)
    , m_user(user)
    , m_sesion(sesion)
{
    ui->setupUi(this);
    ui->lAciertos->setText(QString("Aciertos : %1").arg(m_user->sessions().last().hits()));
    ui->lFallos->setText(QString("Fallos : %1").arg(m_user->sessions().last().hits()));
}

stats::~stats()
{
    delete ui;
}

/*stats::mostrarStats(){

    m_sesion->hits();
}*/
