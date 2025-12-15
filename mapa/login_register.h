#ifndef LOGIN_REGISTER_H
#define LOGIN_REGISTER_H

#include <QLabel>
#include <QMouseEvent>
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include "mainwindow.h"
#include "navdaoexception.h"
#include "navigation.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginRegister;
}
QT_END_NAMESPACE
class QLabel;
class QLineEdit;

class LoginRegister : public QMainWindow
{
    Q_OBJECT
public:
    LoginRegister(QWidget *parent = nullptr);
    ~LoginRegister();
    void mostrarLogin();

private slots:
    void onEmailEditingFinished();
    void addUserButton();

private:
    Ui::LoginRegister *ui;
    MainWindow *ventanaPrincipal;
    bool validEmail;
    bool validPassword;
    bool validRepPassword;
    bool validUsername;
    static const int EQUALS = 0;

    void manageError(QLabel *errorLabel, QLineEdit *edit, bool &flag);
    void manageCorrect(QLabel *errorLabel, QLineEdit *edit, bool &flag);

    void showErrorMessage(QLabel *errorLabel, QLineEdit *edit);
    void hideErrorMessage(QLabel *errorLabel, QLineEdit *edit);

    void checkEmail();
    void checkPassword();
    void checkEqualPassword();
    void checkUserName();
    void user_contr_correct();

    void updateAcceptEnabled();
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
