#ifndef PERFIL_H
#define PERFIL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Perfil;
}
QT_END_NAMESPACE

class Perfil : public QMainWindow
{
    Q_OBJECT

public:
    explicit Perfil(QWidget *parent = nullptr);
    ~Perfil();

private:
    Ui::Perfil *ui;
};

#endif // PERFIL_H
