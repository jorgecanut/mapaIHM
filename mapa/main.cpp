#include "mainwindow.h"
#include "login_register.h"
#include "perfil.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginRegister login;
    //login.show();
    MainWindow w;

    w.show();
    Perfil perfil;
    //perfil.show();

    return a.exec();
}
