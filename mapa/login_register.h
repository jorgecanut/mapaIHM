#ifndef LOGIN_REGISTER_H
#define LOGIN_REGISTER_H

#include <QLabel>
#include <QLineEdit>
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

private slots:
    void onEmailEditingFinished();
    void onPasswordEditingFinished();
    void onUserEditingFinished();

    void onAcceptClicked();

private:
    Ui::LoginRegister *ui;
    MainWindow *ventanaPrincipal;
    bool validEmail;
    bool validPassword;
    bool equalPasswords;

    void manageError(QLabel *errorLabel, QLineEdit *edit, bool &flag);
    void manageCorrect(QLabel *errorLabel, QLineEdit *edit, bool &flag);

    void showErrorMessage(QLabel *errorLabel, QLineEdit *edit);
    void hideErrorMessage(QLabel *errorLabel, QLineEdit *edit);

    void checkEmail();
    void checkPassword();
    void checkEquals();

    void updateAcceptEnabled();
};






// Esto es una chatgepeteada del marc que flipas
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
