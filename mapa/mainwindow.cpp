#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login_register.h"
#include "navigation.h"
#include <QWheelEvent>
#include <QPen>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
    , view(new QGraphicsView(this))
    , escalado(0.2)
{
    ui->setupUi(this);

    setWindowTitle("Carta Náutica");
    view->setScene(scene);
    setCentralWidget(view);

    QPixmap pm(":/icons/icons/carta_nautica.jpg");
    QGraphicsPixmapItem *item = scene->addPixmap(pm);
    item->setZValue(0);

    view->scale(escalado, escalado);
    view->setDragMode(QGraphicsView::ScrollHandDrag);

    QAction *actZoomIn = ui->toolBar->addAction("+");
    QAction *actZoomOut = ui->toolBar->addAction("-");

    QAction *ponerRegla = ui->toolBar->addAction("Regla");
    QAction *ponerTransportador = ui->toolBar->addAction("Transportador");
    QAction *ponerCompas = ui->toolBar->addAction("Compas");

    connect(actZoomIn, &QAction::triggered, this, &MainWindow::zoomIn);
    connect(actZoomOut, &QAction::triggered, this, &MainWindow::zoomOut);

    connect(ponerRegla, &QAction::triggered, this, &MainWindow::regla);
    connect(ponerTransportador, &QAction::triggered, this, &MainWindow::transportador);
    connect(ponerCompas, &QAction::triggered, this, &MainWindow::compas);

    view->viewport()->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::zoomIn(){
    applyZoom(1.15);
}

void MainWindow::zoomOut(){
    applyZoom(1.0 / 1.15);
}

void MainWindow::applyZoom(double factor){
    double newScale = escalado * factor;
    const double minScale = 0.1;
    const double maxScale = 1;

    if (newScale < minScale){
        factor = minScale / escalado;
        newScale = minScale;
    }
    else if (newScale > maxScale){
        factor = maxScale / escalado;
        newScale = maxScale;
    }
    view->scale(factor, factor);
    escalado = newScale;

    actualizarEscalaHerramientas();
}

void MainWindow::actualizarEscalaHerramientas(){
    double escalaHerramienta = 1.0 / escalado;

    if (reglaPuesta && reglaActual){
        // Mantener la escala relativa al zoom
        qreal escalaActual = reglaActual->scale();
        qreal factorBase = escalaActual * escalado; // Escala base sin zoom
        reglaActual->setScale(factorBase / escalado);
    }

    if (transportadorPuesto && transportadorActual){
        qreal escalaActual = transportadorActual->scale();
        qreal factorBase = escalaActual * escalado;
        transportadorActual->setScale(factorBase / escalado);
    }

    if (compasPuesto && compasActual){
        qreal escalaActual = compasActual->scale();
        qreal factorBase = escalaActual * escalado;
        compasActual->setScale(factorBase / escalado);
    }
}

void MainWindow::regla(){
    if (reglaPuesta){
        scene->removeItem(reglaActual);
        delete reglaActual;
        reglaActual = nullptr;
        reglaPuesta = false;
    }

    creandoRegla = true;
    view->setDragMode(QGraphicsView::NoDrag);
    view->setCursor(Qt::CrossCursor);
}

void MainWindow::transportador(){
    if (transportadorPuesto){
        scene->removeItem(transportadorActual);
        delete transportadorActual;
        transportadorActual = nullptr;
        transportadorPuesto = false;
    }

    creandoTransportador = true;
    view->setDragMode(QGraphicsView::NoDrag);
    view->setCursor(Qt::CrossCursor);
}

void MainWindow::compas(){
    if (compasPuesto){
        scene->removeItem(compasActual);
        delete compasActual;
        compasActual = nullptr;
        compasPuesto = false;
    }

    creandoCompas = true;
    view->setDragMode(QGraphicsView::NoDrag);
    view->setCursor(Qt::CrossCursor);
}

void MainWindow::finalizarRegla(QPointF puntoFinal){
    if (lineaGuiaRegla){
        scene->removeItem(lineaGuiaRegla);
        delete lineaGuiaRegla;
        lineaGuiaRegla = nullptr;
    }

    reglaActual = new QGraphicsSvgItem(":icons/icons/ruler.svg");
    reglaActual->setFlag(QGraphicsItem::ItemIsMovable);
    reglaActual->setFlag(QGraphicsItem::ItemIsSelectable);

    QPointF centro = (puntoInicioRegla + puntoFinal) / 2.0;
    qreal dx = puntoFinal.x() - puntoInicioRegla.x();
    qreal dy = puntoFinal.y() - puntoInicioRegla.y();
    qreal distancia = qSqrt(dx * dx + dy * dy);
    qreal angulo = qAtan2(dy, dx) * 180.0 / M_PI;

    reglaActual->setTransformOriginPoint(reglaActual->boundingRect().center());

    qreal anchoRegla = reglaActual->boundingRect().width();
    qreal escalaLongitud = distancia / anchoRegla;
    qreal escalaZoom = 1.0 / escalado;

    reglaActual->setScale(escalaLongitud * escalaZoom);
    reglaActual->setRotation(angulo);
    reglaActual->setPos(centro);
    reglaActual->setZValue(100);

    scene->addItem(reglaActual);

    reglaPuesta = true;
    creandoRegla = false;

    view->setCursor(Qt::ArrowCursor);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
}

void MainWindow::finalizarTransportador(QPointF puntoFinal){
    if (lineaGuiaTransportador){
        scene->removeItem(lineaGuiaTransportador);
        delete lineaGuiaTransportador;
        lineaGuiaTransportador = nullptr;
    }

    transportadorActual = new QGraphicsSvgItem(":icons/icons/transportador.svg");
    transportadorActual->setFlag(QGraphicsItem::ItemIsMovable);
    transportadorActual->setFlag(QGraphicsItem::ItemIsSelectable);

    qreal dx = puntoFinal.x() - puntoInicioTransportador.x();
    qreal dy = puntoFinal.y() - puntoInicioTransportador.y();
    qreal distancia = qSqrt(dx * dx + dy * dy);
    qreal angulo = qAtan2(dy, dx) * 180.0 / M_PI;

    transportadorActual->setTransformOriginPoint(transportadorActual->boundingRect().center());

    // Escalar el transportador según la distancia dibujada
    qreal anchoTransportador = transportadorActual->boundingRect().width();
    qreal escalaDistancia = (distancia * 2) / anchoTransportador; // *2 porque el diámetro es el doble del radio
    qreal escalaZoom = 1.0 / escalado;

    transportadorActual->setScale(escalaDistancia * escalaZoom);
    transportadorActual->setRotation(angulo);
    transportadorActual->setPos(puntoInicioTransportador);
    transportadorActual->setZValue(100);

    scene->addItem(transportadorActual);

    transportadorPuesto = true;
    creandoTransportador = false;

    view->setCursor(Qt::ArrowCursor);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
}

void MainWindow::finalizarCompas(QPointF puntoFinal){
    if (circuloGuia){
        scene->removeItem(circuloGuia);
        delete circuloGuia;
        circuloGuia = nullptr;
    }

    if (lineaGuiaCompas){
        scene->removeItem(lineaGuiaCompas);
        delete lineaGuiaCompas;
        lineaGuiaCompas = nullptr;
    }

    compasActual = new QGraphicsSvgItem(":icons/icons/compass_leg.svg");
    compasActual->setFlag(QGraphicsItem::ItemIsMovable);
    compasActual->setFlag(QGraphicsItem::ItemIsSelectable);

    qreal dx = puntoFinal.x() - centroCompas.x();
    qreal dy = puntoFinal.y() - centroCompas.y();
    qreal radio = qSqrt(dx * dx + dy * dy);
    qreal angulo = qAtan2(dy, dx) * 180.0 / M_PI;

    compasActual->setTransformOriginPoint(compasActual->boundingRect().center());

    // Escalar el compás según el radio dibujado
    qreal alturaCompas = compasActual->boundingRect().height();
    qreal escalaRadio = radio / alturaCompas;
    qreal escalaZoom = 1.0 / escalado;

    compasActual->setScale(escalaRadio * escalaZoom);
    compasActual->setRotation(angulo - 90); // -90 porque el compás apunta hacia arriba por defecto
    compasActual->setPos(centroCompas);
    compasActual->setZValue(100);

    scene->addItem(compasActual);

    compasPuesto = true;
    creandoCompas = false;

    view->setCursor(Qt::ArrowCursor);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
}

void MainWindow::cancelarCreacion(){
    if (lineaGuiaRegla){
        scene->removeItem(lineaGuiaRegla);
        delete lineaGuiaRegla;
        lineaGuiaRegla = nullptr;
    }

    if (lineaGuiaTransportador){
        scene->removeItem(lineaGuiaTransportador);
        delete lineaGuiaTransportador;
        lineaGuiaTransportador = nullptr;
    }

    if (circuloGuia){
        scene->removeItem(circuloGuia);
        delete circuloGuia;
        circuloGuia = nullptr;
    }

    if (lineaGuiaCompas){
        scene->removeItem(lineaGuiaCompas);
        delete lineaGuiaCompas;
        lineaGuiaCompas = nullptr;
    }

    creandoRegla = false;
    creandoTransportador = false;
    creandoCompas = false;

    view->setCursor(Qt::ArrowCursor);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
}

bool MainWindow::eventFilterRegla(QMouseEvent *mouseEvent){
    QPointF scenePos = view->mapToScene(mouseEvent->pos());

    if (mouseEvent->type() == QEvent::MouseButtonPress &&
        mouseEvent->button() == Qt::LeftButton){

        puntoInicioRegla = scenePos;

        QPen pen(Qt::DashLine);
        pen.setColor(Qt::red);
        pen.setWidth(2);
        lineaGuiaRegla = scene->addLine(QLineF(puntoInicioRegla, puntoInicioRegla), pen);
        lineaGuiaRegla->setZValue(1000);

        return true;
    }
    else if (mouseEvent->type() == QEvent::MouseMove && lineaGuiaRegla){
        lineaGuiaRegla->setLine(QLineF(puntoInicioRegla, scenePos));
        return true;
    }
    else if (mouseEvent->type() == QEvent::MouseButtonPress &&
             mouseEvent->button() == Qt::RightButton){
        cancelarCreacion();
        return true;
    }
    else if (mouseEvent->type() == QEvent::MouseButtonRelease &&
             mouseEvent->button() == Qt::LeftButton && lineaGuiaRegla){
        finalizarRegla(scenePos);
        return true;
    }

    return false;
}

bool MainWindow::eventFilterTransportador(QMouseEvent *mouseEvent){
    QPointF scenePos = view->mapToScene(mouseEvent->pos());

    if (mouseEvent->type() == QEvent::MouseButtonPress &&
        mouseEvent->button() == Qt::LeftButton){

        puntoInicioTransportador = scenePos;

        QPen pen(Qt::DashLine);
        pen.setColor(Qt::blue);
        pen.setWidth(2);
        lineaGuiaTransportador = scene->addLine(QLineF(puntoInicioTransportador, puntoInicioTransportador), pen);
        lineaGuiaTransportador->setZValue(1000);

        return true;
    }
    else if (mouseEvent->type() == QEvent::MouseMove && lineaGuiaTransportador){
        lineaGuiaTransportador->setLine(QLineF(puntoInicioTransportador, scenePos));
        return true;
    }
    else if (mouseEvent->type() == QEvent::MouseButtonPress &&
             mouseEvent->button() == Qt::RightButton){
        cancelarCreacion();
        return true;
    }
    else if (mouseEvent->type() == QEvent::MouseButtonRelease &&
             mouseEvent->button() == Qt::LeftButton && lineaGuiaTransportador){
        finalizarTransportador(scenePos);
        return true;
    }

    return false;
}

bool MainWindow::eventFilterCompas(QMouseEvent *mouseEvent){
    QPointF scenePos = view->mapToScene(mouseEvent->pos());

    if (mouseEvent->type() == QEvent::MouseButtonPress &&
        mouseEvent->button() == Qt::LeftButton){

        centroCompas = scenePos;

        QPen pen(Qt::DashLine);
        pen.setColor(Qt::green);
        pen.setWidth(2);

        // Crear círculo guía
        circuloGuia = scene->addEllipse(centroCompas.x(), centroCompas.y(), 0, 0, pen);
        circuloGuia->setZValue(1000);

        // Crear línea guía del radio
        lineaGuiaCompas = scene->addLine(QLineF(centroCompas, centroCompas), pen);
        lineaGuiaCompas->setZValue(1000);

        return true;
    }
    else if (mouseEvent->type() == QEvent::MouseMove && circuloGuia){
        qreal dx = scenePos.x() - centroCompas.x();
        qreal dy = scenePos.y() - centroCompas.y();
        qreal radio = qSqrt(dx * dx + dy * dy);

        // Actualizar círculo
        circuloGuia->setRect(centroCompas.x() - radio, centroCompas.y() - radio,
                             radio * 2, radio * 2);

        // Actualizar línea del radio
        lineaGuiaCompas->setLine(QLineF(centroCompas, scenePos));

        return true;
    }
    else if (mouseEvent->type() == QEvent::MouseButtonPress &&
             mouseEvent->button() == Qt::RightButton){
        cancelarCreacion();
        return true;
    }
    else if (mouseEvent->type() == QEvent::MouseButtonRelease &&
             mouseEvent->button() == Qt::LeftButton && circuloGuia){
        finalizarCompas(scenePos);
        return true;
    }

    return false;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == view->viewport()){
        // Manejo de creación de herramientas
        if (creandoRegla &&
            (event->type() == QEvent::MouseButtonPress ||
             event->type() == QEvent::MouseMove ||
             event->type() == QEvent::MouseButtonRelease)){
            return eventFilterRegla(static_cast<QMouseEvent*>(event));
        }

        if (creandoTransportador &&
            (event->type() == QEvent::MouseButtonPress ||
             event->type() == QEvent::MouseMove ||
             event->type() == QEvent::MouseButtonRelease)){
            return eventFilterTransportador(static_cast<QMouseEvent*>(event));
        }

        if (creandoCompas &&
            (event->type() == QEvent::MouseButtonPress ||
             event->type() == QEvent::MouseMove ||
             event->type() == QEvent::MouseButtonRelease)){
            return eventFilterCompas(static_cast<QMouseEvent*>(event));
        }

        // Manejo de zoom con CTRL + rueda
        if (event->type() == QEvent::Wheel) {
            QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);

            if (wheelEvent->modifiers() & Qt::CTRL) {
                double factor = 1.15;
                if (wheelEvent->angleDelta().y() > 0)
                    applyZoom(factor);
                else
                    applyZoom(1.0 / factor);

                return true;
            }
        }
    }

    return QMainWindow::eventFilter(obj, event);
}
