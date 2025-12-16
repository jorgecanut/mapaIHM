#include "textitem.h"
#include "mainwindow.h"

void EditableTextItem::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        clearFocus();
    } else {
        QGraphicsTextItem::keyPressEvent(event);
    }
}

void EditableTextItem::focusOutEvent(QFocusEvent *event){
    setTextInteractionFlags(Qt::NoTextInteraction);
    clearFocus();

    if (mainWindow) {
        mainWindow->salirModoTexto();
    }

    QGraphicsTextItem::focusOutEvent(event);
}

void EditableTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    setTextInteractionFlags(Qt::TextEditorInteraction);
    setFocus();
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}
