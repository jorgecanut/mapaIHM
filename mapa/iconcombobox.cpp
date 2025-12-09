#include "iconcombobox.h"

IconComboBox::IconComboBox(QWidget *parent)
    : QComboBox(parent) {
    setIconSize(QSize(70, 150));  // Configura el tamaño del ícono
}

void IconComboBox::addIconItem(const QString &iconPath) {
    QIcon icon(iconPath);
    // Agregar ítem solo con ícono y sin texto
    addItem(icon,"", QVariant(iconPath));
}

QString IconComboBox::selectedIconName() const {
    // Retorna el path completo del ícono seleccionado
    return currentData().toString();
}

QIcon IconComboBox::selectedIcon() const {
    // Retorna el ícono del ítem seleccionado
    return itemIcon(currentIndex());
}

void IconComboBox::setCurrentIcon(const QString &iconPath) {
    // Selecciona el ítem con el ícono correspondiente
    for (int i = 0; i < count(); ++i) {
        if (itemData(i).toString() == iconPath) {
            setCurrentIndex(i);
            return;
        }
    }
}
