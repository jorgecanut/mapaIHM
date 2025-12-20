#ifndef STATS_H
#define STATS_H

#include <QMainWindow>
#include <mainwindow.h>

namespace Ui {
class stats;
}

class stats : public QMainWindow
{
    Q_OBJECT

public:
    explicit stats(User *m_user,Session *sesion,QWidget *parent = nullptr);
    ~stats();

private:
    Ui::stats *ui;
    User *m_user;
    Session *m_sesion;

    struct statsDia{
        int sesiones = 0;
        int hits = 0;
        int faults = 0;
    };

    void refrescarRango(const QDate &inicio, const QDate &fin);
    void ajustarRango(); // fin siempre >= inicio
};

#endif // STATS_H
