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
    , reglaActual(nullptr)
    , compasActual(nullptr)
    , transportadorActual(nullptr)
    , reglaPuesta(false)
    , transportadorPuesto(false)
    , compasPuesto(false)
    , herramientaPendiente(Ninguna)
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

    connect(ui->actionZoom_In, &QAction::triggered, this, &MainWindow::zoomIn);
    connect(ui->actionZoom_Out, &QAction::triggered, this, &MainWindow::zoomOut);

    connect(ui->actionRegla, &QAction::triggered, this, &MainWindow::regla);
    connect(ui->actionTransportador, &QAction::triggered, this, &MainWindow::transportador);
    connect(ui->actionCompas, &QAction::triggered, this, &MainWindow::compas);

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

    if (reglaPuesta){
        reglaActual->setScale(0.5/escalado);
    }
    if (transportadorPuesto){
        transportadorActual->setScale(0.1/escalado);
    }
    if (compasPuesto){
        compasActual->setScale(0.5/escalado);
    }
}

void MainWindow::regla(){
    if (reglaPuesta){
        scene->removeItem(reglaActual);
        delete reglaActual;
        reglaActual = nullptr;
        reglaPuesta = false;
    }
    else{
        herramientaPendiente = ReglaPendiente;
    }
}

void MainWindow::transportador(){
    if (transportadorPuesto){
        scene->removeItem(transportadorActual);
        delete transportadorActual;
        transportadorActual = nullptr;
        transportadorPuesto = false;
    }
    else{
        herramientaPendiente = TransportadorPendiente;
    }
}

void MainWindow::compas(){
    if (compasPuesto){
        scene->removeItem(compasActual);
        delete compasActual;
        compasActual = nullptr;
        compasPuesto = false;
    }
    else {
        herramientaPendiente = CompasPendiente;
    }

}

void MainWindow::ponerSvg(QGraphicsSvgItem *svgItem, double escaladoHerramienta){
    svgItem->setFlag(QGraphicsItem::ItemIsMovable);
    svgItem->setFlag(QGraphicsItem::ItemIsSelectable);
    svgItem->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    svgItem->setTransformOriginPoint(svgItem->boundingRect().center());
    svgItem->setScale(escaladoHerramienta);

    scene->addItem(svgItem);
    view->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::rotarSvg(QGraphicsItem *svgItem, int rotacion){
    qreal anguloActual = svgItem->rotation();
    svgItem->setRotation(anguloActual+rotacion);
}

// Hecho con chat
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == view->viewport() && event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);

        // ZOOM
        if (wheelEvent->modifiers() & Qt::CTRL) {
            double factor = 1.15;
            if (wheelEvent->angleDelta().y() > 0)
                applyZoom(factor);
            else
                applyZoom(1.0 / factor);

            return true;
        }
        // ROTAR HERRAMIENTAS
        else if (wheelEvent->modifiers() & Qt::SHIFT) {
            QGraphicsItem *itemSeleccionado = nullptr;
            QList<QGraphicsItem*> items = scene->selectedItems();

            if (!items.isEmpty()) {
                itemSeleccionado = items.first();
                if (wheelEvent->angleDelta().y() > 0)
                    rotarSvg(itemSeleccionado, 5);
                else
                    rotarSvg(itemSeleccionado, -5);

                return true;
            }
        }
    }

    if (obj == view->viewport() && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        if (mouseEvent->button() == Qt::LeftButton &&
            herramientaPendiente != Ninguna) {

            QPointF posScene = view->mapToScene(mouseEvent->pos());

            switch (herramientaPendiente) {
            case ReglaPendiente:
                reglaActual = new QGraphicsSvgItem(":/icons/icons/ruler2.svg");
                reglaPuesta = true;
                ponerSvg(reglaActual, 0.3/escalado);
                reglaActual->setPos(posScene - reglaActual->boundingRect().center());
                break;

            case TransportadorPendiente:
                transportadorActual = new QGraphicsSvgItem(":/icons/icons/transportador.svg");
                transportadorPuesto = true;
                ponerSvg(transportadorActual, 0.15/escalado);
                transportadorActual->setPos(posScene - transportadorActual->boundingRect().center());
                break;

            case CompasPendiente:
                compasActual = new QGraphicsSvgItem(":/icons/icons/compass_leg.svg");
                compasPuesto = true;
                ponerSvg(compasActual, 0.5/escalado);
                compasActual->setPos(posScene - compasActual->boundingRect().center());
                break;

            default:
                break;
            }

            herramientaPendiente = Ninguna;
            return true;
        }
    }

    return QMainWindow::eventFilter(obj, event);
}
