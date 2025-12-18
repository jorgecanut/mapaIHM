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

    //void mostrarStats();
};

#endif // STATS_H
