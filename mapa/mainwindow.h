#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsSvgItem>
#include <QWheelEvent>
#include <QShortcut>
#include <QWidget>
#include <QSlider>
#include <QPushButton>
#include <QMouseEvent>
#include <QColorDialog>
#include <QDockWidget>
#include <QRandomGenerator>

#include <navigation.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(User *user,QWidget *parent = nullptr);
    void salirModoTexto();
    ~MainWindow();

private:
    // ------- UI ---------
    Ui::MainWindow *ui;
    User *m_user;
    QGraphicsScene *scene;
    QGraphicsView *view;
    bool dockExpandido = false;
    int dockWidthExpandido = 250;

    //------Preguntas-------
    int preguntaActual = 0;
    QVector<Problem> listaPreguntas;
    void cargarPregunta(int index);
    void reseteoPreguntas();

    float escalado;

    // ---- HERRAMIENTAS ----
    enum class HerramientaActiva {
        Ninguna,
        Lapiz,
        Goma,
        Texto,
        Regla,
        Compas,
        Transportador
    };

    HerramientaActiva herramientaActual;


    // ---- HERRAMIENTAS ITEM ---------
    QGraphicsSvgItem *reglaActual;
    QGraphicsSvgItem *compasActual;
    QGraphicsSvgItem *transportadorActual;

    bool reglaPuesta;
    bool transportadorPuesto;
    bool compasPuesto;

    // ----- LINEAS -----
    QPointF inicioLinea;
    QGraphicsLineItem *lineaActual;

    QColor colorLinea;
    float grosorLinea;

    // ------- TEXTO -------
    QGraphicsTextItem *textoActual;
    QColor colorTexto;
    int tamañoTexto;


    // ----- COSAS UTILES ------
    void setHerramienta(HerramientaActiva nueva);
    void applyZoom(double factor);
    void ponerSvg(QGraphicsSvgItem *svgItem, double escaladoHerramienta);
    void rotarSvg(QGraphicsItem *svgItem, int rotacion);
    void rotarSeleccion(int angulo);
    QPointF posicionRaton();
    void reset();
    void toggleDockPreguntas();

private slots:
    void zoomIn();
    void zoomOut();

    void actualizarAcciones();
    void rotarHorario();
    void rotarAntiHorario();

    void regla();
    void transportador();
    void compas();

    void abrirPerfil();
    void cerrarSesion();

    void lapiz();
    void goma();
    void texto();

    //---------Preguntas------------
    void comprobarRespuestas();

protected:
    // Para el zoom y la rueda
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // MAINWINDOW_H
