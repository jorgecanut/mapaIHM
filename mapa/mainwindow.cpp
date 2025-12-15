#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login_register.h"
#include "perfil.h"
#include "login_register.h"



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
    , colorLinea(Qt::black)
    , grosorLinea(2)
    , lapizActivo(false)

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

    // Desactivadas hasta que se selecciona algo
    ui->actionRotar_horario->setEnabled(false);
    ui->actionRotar_antihorario->setEnabled(false);
    connect(ui->actionRotar_horario, &QAction::triggered, this, &MainWindow::rotarHorario);
    connect(ui->actionRotar_antihorario, &QAction::triggered, this, &MainWindow::rotarAntiHorario);

    connect(ui->actionLapiz, &QAction::triggered, this, &MainWindow::lapiz);

    connect(scene, &QGraphicsScene::selectionChanged, this, &MainWindow::actualizarAcciones);

    connect(ui->actionRegla, &QAction::triggered, this, &MainWindow::regla);
    connect(ui->actionTransportador, &QAction::triggered, this, &MainWindow::transportador);
    connect(ui->actionCompas, &QAction::triggered, this, &MainWindow::compas);
    connect(ui->actionMi_Perfil, &QAction::triggered,this,&MainWindow::abrirPerfil);
    connect(ui->actionCerrar_Sesion, &QAction::triggered,this,&MainWindow::cerrarSesion);

    connect(ui->actionResetear, &QAction::triggered, this, &MainWindow::reset);
    // Esto es para poder hacer shift scroll no quitar
    view->viewport()->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ------------- ZOOM ---------------
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
        reglaActual->setScale(0.3/escalado);
    }
    if (transportadorPuesto){
        transportadorActual->setScale(0.15/escalado);
    }
    if (compasPuesto){
        compasActual->setScale(0.5/escalado);
    }
}

// --------- ROTACION --------------
void MainWindow::actualizarAcciones(){
    bool hay_seleccion = !scene->selectedItems().isEmpty();
    ui->actionRotar_horario->setEnabled(hay_seleccion);
    ui->actionRotar_antihorario->setEnabled(hay_seleccion);
}

void MainWindow::rotarHorario(){ rotarSeleccion(5); }
void MainWindow::rotarAntiHorario(){ rotarSeleccion(-5); }

void MainWindow::rotarSeleccion(int angulo){
    QList<QGraphicsItem*> items = scene->selectedItems();
    if (!items.isEmpty()){
        QGraphicsItem *item = items.first();
        item->setRotation(item->rotation() + angulo);
    }
}

// ------- HERRAMIENTAS -------------
QPointF MainWindow::posicionRaton(){
    QPoint posGlobal = QCursor::pos();
    QPoint posView = view->mapFromGlobal(posGlobal);
    return view->mapToScene(posView);

}

void MainWindow::regla() {
    toggleHerramienta(reglaActual, reglaPuesta, ":/icons/icons/ruler2.svg", 0.3);
}
void MainWindow::transportador() {
    toggleHerramienta(transportadorActual, transportadorPuesto, ":/icons/icons/transportador.svg", 0.15);
}
void MainWindow::compas() {
    toggleHerramienta(compasActual, compasPuesto, ":/icons/icons/compass_leg.svg", 0.5);
}


void MainWindow::toggleHerramienta(QGraphicsSvgItem* &herr, bool &puesta, const QString &icono, double escala){
    if (puesta){
        scene->removeItem(herr);
        delete herr;
        herr = nullptr;
        puesta = false;
    } else {
        lapizActivo = false;
        herr = new QGraphicsSvgItem(icono);
        ponerSvg(herr, escala/escalado);
        herr->setPos(posicionRaton() - herr->boundingRect().center());
        puesta = true;
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


// -------------------- PERFIL / SESIÓN --------------------
void MainWindow::abrirPerfil(){
    Perfil *perfil = new Perfil(this);
    perfil->show();
}

void MainWindow::cerrarSesion(){
    LoginRegister *login = new LoginRegister();
    login->show();
    login->mostrarLogin();
    this->close();
}


// ------------------ RESET ---------------
void MainWindow::reset(){
    // Elimina herramientas de la escena
    if (reglaPuesta){
        scene->removeItem(reglaActual);
        delete reglaActual;
        reglaActual = nullptr;
        reglaPuesta = false;
    }
    if (transportadorPuesto){
        scene->removeItem(transportadorActual);
        delete transportadorActual;
        transportadorActual = nullptr;
        transportadorPuesto = false;
    }
    if (compasPuesto){
        scene->removeItem(compasActual);
        delete compasActual;
        compasActual = nullptr;
        compasPuesto = false;
    }

    escalado = 0.2;
    view->resetTransform();
    view->scale(escalado, escalado);

    scene->clearSelection();
}

// ---------- DIBUJAR -------------
void MainWindow::lapiz(){
    if(lapizActivo)
        lapizActivo = false;
    else
        lapizActivo = true;
}

// Para poder hacer zoom con el ratón
bool MainWindow::eventFilter(QObject *obj, QEvent *event){
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
    }

    if (obj == view->viewport() && lapizActivo){
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

            if (mouseEvent->button() == Qt::LeftButton) {
                inicioLinea = view->mapToScene(mouseEvent->pos());
                lineaActual = nullptr;
            }
            return true;
        }


        else if (event->type() == QEvent::MouseMove) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QPointF posActual = view->mapToScene(mouseEvent->pos());

            if (mouseEvent->buttons() & Qt::LeftButton) {
                if (!lineaActual) {
                    lineaActual = new QGraphicsLineItem(
                        QLineF(inicioLinea, posActual)
                        );

                    QPen pen(colorLinea, grosorLinea);
                    lineaActual->setPen(pen);

                    lineaActual->setFlag(QGraphicsItem::ItemIsMovable);
                    lineaActual->setFlag(QGraphicsItem::ItemIsSelectable);
                    lineaActual->setFlag(QGraphicsItem::ItemIsFocusable);

                    scene->addItem(lineaActual);
                } else {
                    lineaActual->setLine(
                        QLineF(inicioLinea, posActual)
                        );
                }
            }
            return true;
        }

        else if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QPointF finLinea = view->mapToScene(mouseEvent->pos());

            if (!lineaActual) {
                QGraphicsEllipseItem *punto = new QGraphicsEllipseItem(
                    finLinea.x() - grosorLinea,
                    finLinea.y() - grosorLinea,
                    grosorLinea * 2,
                    grosorLinea * 2
                    );

                punto->setBrush(colorLinea);
                punto->setPen(QPen(colorLinea));

                punto->setFlag(QGraphicsItem::ItemIsMovable);
                punto->setFlag(QGraphicsItem::ItemIsSelectable);

                scene->addItem(punto);
            }

            lineaActual = nullptr;
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}
