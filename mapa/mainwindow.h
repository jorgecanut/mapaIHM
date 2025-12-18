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
    struct EstadoPregunta{
        bool respondida = false;
        int seleccion = -1;
        int correcta = -1;
        bool acierto = false;
    };

    Session sesion;
    int preguntaActual = 0;
    int aciertos = 0;
    int fallos = 0;
    QSet<int> preguntasRespondidas;
    QVector<EstadoPregunta> estadosPreguntas;
    QVector<Problem> listaPreguntas;
    void cargarPregunta(int index);
    void aplicarEstadoPregunta(int index);


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

    qreal rotacionOriginalRegla;
    bool reglaActiva;
    bool compasActivo;
    bool transportadorActivo;
    bool reglaApartada = false;


    // ----- LINEAS -----
    QPointF inicioLinea;
    QGraphicsLineItem *lineaActual;
    QPointF posicionOriginalRegla;

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
    void moverRegla();

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

    void estadisticas();
    //---------Preguntas------------
    void comprobarRespuestas();

protected:
    // Para el zoom y la rueda
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // MAINWINDOW_H
