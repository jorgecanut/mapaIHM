#ifndef TEXTITEM_H
#define TEXTITEM_H
#include "mainwindow.h"

class EditableTextItem : public QGraphicsTextItem {
public:
    EditableTextItem(MainWindow* mw)
        : mainWindow(mw) {}

protected:
    void keyPressEvent(QKeyEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
private:
    MainWindow* mainWindow;
};

#endif // TEXTITEM_H
