#ifndef PREGUNTAS_H
#define PREGUNTAS_H

#include <QWidget>

namespace Ui {
class Preguntas;
}

class Preguntas : public QWidget
{
    Q_OBJECT

public:
    explicit Preguntas(QWidget *parent = nullptr);
    ~Preguntas();

private:
    Ui::Preguntas *ui;
};

#endif // PREGUNTAS_H
