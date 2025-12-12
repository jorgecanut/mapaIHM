#ifndef PERFIL_H
#define PERFIL_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include "mainwindow.h"

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
    bool validEmail;
    bool validPassword;
    bool validRepPassword;
    bool validAge;

    void manageError(QLabel *errorLabel, QLineEdit *edit, bool &flag);
    void manageCorrect(QLabel *errorLabel, QLineEdit *edit, bool &flag);

    void showErrorMessage(QLabel *errorLabel, QLineEdit *edit);
    void hideErrorMessage(QLabel *errorLabel, QLineEdit *edit);

    void checkEmail();
    void checkPassword();
    void checkDate();

    void updateAcceptEnabled();

private slots:
    void onEmailEditingFinished();

signals:
    void clicked();
};

#endif // PERFIL_H
