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


    if(repPassword != password){
        return false;
    }
    return true;
}
bool Utils::checkUsuario(const QString &usuario)
{
    // 1. Validar longitud entre 6 y 15
    if (usuario.length() < 6 || usuario.length() > 15) {
        return false;
    }

    // 2. Recorrer cada carácter para verificar las reglas
    for (const QChar &c : usuario) {

        // Verificar si es espacio (No permitido)
        if (c.isSpace()) {
            return false;
        }

        // Verificar si es un carácter permitido:
        // Letra, número, guion '-' o subguion '_'
        bool isLetterOrDigit = c.isLetterOrNumber();
        bool isSpecialAllowed = (c == '-' || c == '_');

        if (!isLetterOrDigit && !isSpecialAllowed) {
            // Si no es ninguno de los anteriores, es un carácter inválido
            return false;
        }
    }

    // Si pasó todas las pruebas anteriores
    return true;
}
