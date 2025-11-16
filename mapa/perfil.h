#ifndef PERFIL_H
#define PERFIL_H

#include <QWidget>

namespace Ui {
class Perfil;
}

class Perfil : public QWidget
{
    Q_OBJECT

public:
    explicit Perfil(QWidget *parent = nullptr);
    ~Perfil();

private:
    Ui::Perfil *ui;
};

#endif // PERFIL_H
