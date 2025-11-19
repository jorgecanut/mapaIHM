#ifndef LOGIN_REGISTER_H
#define LOGIN_REGISTER_H

#include <QLabel>
#include <QMouseEvent>
#include <QMainWindow>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginRegister;
}
QT_END_NAMESPACE

class LoginRegister : public QMainWindow
{
    Q_OBJECT
public:
    LoginRegister(QWidget *parent = nullptr);
    ~LoginRegister();
private:
    Ui::LoginRegister *ui;
    MainWindow *ventanaPrincipal;
};

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent = nullptr) : QLabel(parent) {}
    ~ClickableLabel() = default;

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override {
        emit clicked();
        QLabel::mousePressEvent(event); // opcional pero recomendable
    }
};

#endif// LOGIN_REGISTER_H
