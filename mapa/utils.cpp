#include "utils.h"
#include <QRegularExpression>

bool Utils::checkEmail(const QString &email)
{
    // Expresión regular sencilla para validar emails básicos
    static QRegularExpression re(
        QStringLiteral("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$"));
    return re.match(email).hasMatch();
}

bool Utils::checkPassword(const QString &password)
{
    // Longitud entre 8 y 15 y combinación de letras y números
    if (password.length() < 8 || password.length() > 15)
        return false;

    bool hasLetter = false;
    bool hasDigit  = false;

    for (const QChar &c : password) {
        if (c.isLetter())
            hasLetter = true;
        if (c.isDigit())
            hasDigit = true;
    }
    return hasLetter && hasDigit;
}

bool Utils::checkRepPassword(const QString &repPassword, const QString &password){

    //Comprobamos primero si tienes el mismo número de carácteres si no es asi ya no son iguales
    if(password.length() != repPassword.length()){
        return false;
    }

    //Comprobamos letra a letra si son iguales
    for(int i = 0; i <= password.length(); i++){
        if(repPassword[i] != password[i]){
            return false;
        }
    }
    return true;
}
