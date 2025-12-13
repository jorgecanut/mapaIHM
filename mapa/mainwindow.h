#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSvgItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void zoomIn();
    void zoomOut();
    void regla();
    void transportador();
    void compas();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    bool eventFilterRegla(QMouseEvent *mouseEvent);
    bool eventFilterTransportador(QMouseEvent *mouseEvent);
    bool eventFilterCompas(QMouseEvent *mouseEvent);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    double escalado;

    // Herramientas
    QGraphicsSvgItem *reglaActual = nullptr;
    QGraphicsSvgItem *transportadorActual = nullptr;
    QGraphicsSvgItem *compasActual = nullptr;

    bool reglaPuesta = false;
    bool transportadorPuesto = false;
    bool compasPuesto = false;

    // Estado de creación de regla
    bool creandoRegla = false;
    QPointF puntoInicioRegla;
    QGraphicsLineItem *lineaGuiaRegla = nullptr;

    // Estado de creación de transportador
    bool creandoTransportador = false;
    QPointF puntoInicioTransportador;
    QGraphicsLineItem *lineaGuiaTransportador = nullptr;

    // Estado de creación de compás
    bool creandoCompas = false;
    QPointF centroCompas;
    QGraphicsEllipseItem *circuloGuia = nullptr;
    QGraphicsLineItem *lineaGuiaCompas = nullptr;

    void applyZoom(double factor);
    void actualizarEscalaHerramientas();
    void finalizarRegla(QPointF puntoFinal);
    void finalizarTransportador(QPointF puntoFinal);
    void finalizarCompas(QPointF puntoFinal);
    void cancelarCreacion();
};

#endif // MAINWINDOW_H
