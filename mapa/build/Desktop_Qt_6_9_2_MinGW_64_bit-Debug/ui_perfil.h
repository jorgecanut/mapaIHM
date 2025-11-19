/********************************************************************************
** Form generated from reading UI file 'perfil.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERFIL_H
#define UI_PERFIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Perfil
{
public:

    void setupUi(QWidget *Perfil)
    {
        if (Perfil->objectName().isEmpty())
            Perfil->setObjectName("Perfil");
        Perfil->resize(400, 300);

        retranslateUi(Perfil);

        QMetaObject::connectSlotsByName(Perfil);
    } // setupUi

    void retranslateUi(QWidget *Perfil)
    {
        Perfil->setWindowTitle(QCoreApplication::translate("Perfil", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Perfil: public Ui_Perfil {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERFIL_H
