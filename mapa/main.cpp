#include "mainwindow.h"
#include "login_register.h"
#include "perfil.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginRegister login;
    //login.show();
    Perfil perfil;
    //perfil.show();
    MainWindow w;
    w.show();
    return a.exec();
}
