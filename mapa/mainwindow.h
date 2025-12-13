#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsScale>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsSvgItem>
#include <QWheelEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QGraphicsView *view;

    float escalado;
    void applyZoom(double factor);

    QGraphicsSvgItem *reglaActual;
    QGraphicsSvgItem *compasActual;
    QGraphicsSvgItem *transportadorActual;
    bool reglaPuesta = false;
    bool transportadorPuesto = false;
    bool compasPuesto = false;
    void cambiarCursor(QGraphicsSvgItem *svgItem);


private slots:
    void zoomIn();
    void zoomOut();

    void regla();
    void transportador();
    void compas();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};
#endif // MAINWINDOW_H
