/********************************************************************************
** Form generated from reading UI file 'preguntas.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREGUNTAS_H
#define UI_PREGUNTAS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Preguntas
{
public:

    void setupUi(QWidget *Preguntas)
    {
        if (Preguntas->objectName().isEmpty())
            Preguntas->setObjectName("Preguntas");
        Preguntas->resize(400, 300);

        retranslateUi(Preguntas);

        QMetaObject::connectSlotsByName(Preguntas);
    } // setupUi

    void retranslateUi(QWidget *Preguntas)
    {
        Preguntas->setWindowTitle(QCoreApplication::translate("Preguntas", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Preguntas: public Ui_Preguntas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREGUNTAS_H
