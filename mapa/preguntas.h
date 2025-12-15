#ifndef PREGUNTAS_H
#define PREGUNTAS_H

#include <QMainWindow>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Preguntas;
}
QT_END_NAMESPACE

class Preguntas : public QMainWindow
{
    Q_OBJECT

public:
    explicit Preguntas(User *user, QWidget *parent = nullptr);
    ~Preguntas();

private:
    Ui::Preguntas *ui;
    User *m_user;
    void random_pregunta();
};

#endif // PREGUNTAS_H
