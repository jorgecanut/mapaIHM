#ifndef PERFIL_H
#define PERFIL_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <navigation.h>
#include <QMessageBox>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Perfil;
}
QT_END_NAMESPACE

class Perfil : public QDialog
{
    Q_OBJECT

public:
    explicit Perfil(User *user ,QWidget *parent = nullptr);
    ~Perfil();

private:
    Ui::Perfil *ui;
    User *m_user;
    bool validEmail;
    bool validPassword;
    bool validRepPassword;
    bool validAge;
    bool validUsername;

    void configurarAvatar();
    void resizeEvent(QResizeEvent *event) override;

    void loadUserData();

    void manageError(QLabel *errorLabel, QLineEdit *edit, bool &flag);
    void manageCorrect(QLabel *errorLabel, QLineEdit *edit, bool &flag);

    void showErrorMessage(QLabel *errorLabel, QLineEdit *edit);
    void hideErrorMessage(QLabel *errorLabel, QLineEdit *edit);

    void checkEmail();
    void checkPassword();
    void checkDate();


    void seleccionAvatar();

    void updateAcceptEnabled();
private slots:
    void onEmailEditingFinished();
    void updateUserButton();

signals:
    void clicked();
};

#endif // PERFIL_H
