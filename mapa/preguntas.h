#ifndef PREGUNTAS_H
#define PREGUNTAS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Preguntas;
}
QT_END_NAMESPACE

class Preguntas : public QMainWindow
{
    Q_OBJECT

public:
    explicit Preguntas(QWidget *parent = nullptr);
    ~Preguntas();

private:
    Ui::Preguntas *ui;
};

#endif // PREGUNTAS_H
