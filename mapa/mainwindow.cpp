#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login_register.h"
#include "navigation.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
    , view(new QGraphicsView(this))
    , escalado(0.2)
    , reglaPuesta(false)
    , transportadorPuesto(false)
    , compasPuesto(false)
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

    // Esto es para poder hacer shift scroll no quitar
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
    // factor > 1 acerca, factor < 1 aleja
    double newScale = escalado * factor;
    const double minScale = 0.2;
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

    double escaladoHerramienta = 0.2 / escalado;

    if (reglaPuesta){
        reglaActual->setScale(escaladoHerramienta);
    }
    if (transportadorPuesto){
        transportadorActual->setScale(escaladoHerramienta);
    }
    if (compasPuesto){
        compasActual->setScale(escaladoHerramienta*5);
    }



}

void MainWindow::regla(){
    if (reglaPuesta){
        scene->removeItem(reglaActual);
        delete reglaActual;
        reglaPuesta = false;
    }
    else{
        reglaActual = new QGraphicsSvgItem(":icons/icons/ruler.svg");
        ponerSvg(reglaActual, 1);
        reglaPuesta = true;
    }
}

void MainWindow::transportador(){
    if (transportadorPuesto){
        scene->removeItem(transportadorActual);
        delete transportadorActual;
        transportadorPuesto = false;
    }
    else{
        transportadorActual = new QGraphicsSvgItem(":icons/icons/transportador.svg");
        ponerSvg(transportadorActual, 1);
        transportadorPuesto = true;
    }

}

void MainWindow::compas(){
    if (compasPuesto){
        scene->removeItem(compasActual);
        delete compasActual;
        compasPuesto = false;
    }
    else {
        compasActual = new QGraphicsSvgItem(":icons/icons/compass_leg.svg");
        ponerSvg(compasActual, 5);
        compasPuesto = true;
    }

}

void MainWindow::ponerSvg(QGraphicsSvgItem *svgItem, int multiplier){
    svgItem->setFlag(QGraphicsItem::ItemIsMovable);
    svgItem->setFlag(QGraphicsItem::ItemIsSelectable);
    svgItem->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    svgItem->setTransformOriginPoint(svgItem->boundingRect().center());

    QPointF centroVista = view->mapToScene(view->viewport()->rect().center());
    QPointF offset = svgItem->boundingRect().center();
    svgItem->setPos(centroVista - offset);

    // 0.1 para la regla
    double escaladoHerramienta = (0.2 / escalado) * multiplier;
    svgItem->setScale(escaladoHerramienta);

    scene->addItem(svgItem);

    view->setRenderHint(QPainter::Antialiasing);
    view->setDragMode(QGraphicsView::RubberBandDrag);
}

// Hecho con chat
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == view->viewport() && event->type() == QEvent::Wheel) {
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

    return QMainWindow::eventFilter(obj, event);
}

