#ifndef ICONCOMBOBOX_H
#define ICONCOMBOBOX_H

#include <QComboBox>
#include <QIcon>

class IconComboBox : public QComboBox {
    Q_OBJECT

public:
    explicit IconComboBox(QWidget *parent = nullptr);

    void addIconItem(const QString &iconPath);  // Modificar para solo íconos
    QString selectedIconName() const;
    QIcon selectedIcon() const;

    // Método para seleccionar el ítem basado en el ícono (usando el archivo del ícono)
    void setCurrentIcon(const QString &iconPath);
};

#endif // ICONCOMBOBOX_H
