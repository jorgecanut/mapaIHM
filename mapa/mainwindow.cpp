#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login_register.h"
#include "perfil.h"
#include "textitem.h"
#include <stats.h>

MainWindow::MainWindow(User *user, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_user(user)
    , scene(new QGraphicsScene(this))
    , view(new QGraphicsView(this))
    , escalado(0.2)
    , herramientaActual(HerramientaActiva::Ninguna)
    , reglaActual(nullptr)
    , compasActual(nullptr)
    , transportadorActual(nullptr)
    , reglaActiva(false)
    , compasActivo(false)
    , transportadorActivo(false)
    , lineaActual(nullptr)
    , colorLinea(Qt::black)
    , grosorLinea(2)
    , textoActual(nullptr)
    , colorTexto(Qt::black)
    , rotacionActiva(false)
    , pivotPoint(nullptr)

{
    ui->setupUi(this);

    QWidget *spacer = new QWidget(this);

    // 2. Configurarlo para que se expanda y empuje lo que tenga a su derecha
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // 3. Insertarlo en la toolbar JUSTO ANTES de "Mi Perfil"
    // Esto enviará a "Mi Perfil" y a "Cerrar Sesión" al extremo derecho.
    ui->toolBar->insertWidget(ui->actionEstadisticas, spacer);

    QFile file(":/estilos/estilo.qss"); // Ruta al archivo en el recurso
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QString::fromUtf8(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }

    setWindowTitle("Carta Náutica");
    view->setScene(scene);
    setCentralWidget(view);

    QPixmap pm(":/icons/icons/carta_nautica.jpg");
    QGraphicsPixmapItem *item = scene->addPixmap(pm);
    item->setZValue(0);

    view->scale(escalado, escalado);
    view->setDragMode(QGraphicsView::ScrollHandDrag);

    ui->panelLapiz->setParent(view);
    ui->panelLapiz->move(20, 0);
    ui->panelLapiz->raise();
    ui->panelLapiz->hide();

    ui->panelTexto->setParent(view);
    ui->panelTexto->move(20, 0);
    ui->panelTexto->raise();
    ui->panelTexto->hide();


    //--------Preguntas------------
    ui->lPregunta->setVisible(false);
    ui->lIndice->setVisible(false);
    ui->rb1->setVisible(false);
    ui->rb2->setVisible(false);
    ui->rb3->setVisible(false);
    ui->rb4->setVisible(false);
    ui->pbSiguiente->setVisible(false);
    ui->pbRandom->setVisible(false);
    ui->pbAnterior->setVisible(false);
    ui->pbResolverPreguntas->setVisible(false);

    Navigation &nav = Navigation::instance();
    listaPreguntas = nav.problems();
    estadosPreguntas.clear();
    estadosPreguntas.resize(listaPreguntas.size());
    preguntasRespondidas.clear();

    for(int i = 0; i < listaPreguntas.size(); i++){
        const auto &ans = listaPreguntas[i].answers();
        int idxCorrecta = -1;
        for(int j = 0; j < ans.size(); j++){
            if(ans[j].validity()){
                idxCorrecta = j;
                break;
            }
        }
        estadosPreguntas[i].correcta = idxCorrecta;
    }

    if (!listaPreguntas.isEmpty()) {
        preguntaActual = 0;
        cargarPregunta(preguntaActual);
    }

    connect(ui->pbTogglePreguntas, &QPushButton::clicked,this, &MainWindow::toggleDockPreguntas);
    connect(ui->pbSiguiente, &QPushButton::clicked, this, [=](){
        if(preguntaActual< listaPreguntas.size()-1){
            preguntaActual++;
            cargarPregunta(preguntaActual);
        }
    });

    connect(ui->pbAnterior, &QPushButton::clicked, this, [=](){
        if(preguntaActual > 0){
            preguntaActual--;
            cargarPregunta(preguntaActual);
        }
    });

    connect(ui->pbRandom, &QPushButton::clicked, this, [=](){
        if (listaPreguntas.isEmpty()) {
            qDebug() << "No hay preguntas cargadas para seleccionar una aleatoria.";
            return;
        }
        preguntaActual = QRandomGenerator::global()->bounded(listaPreguntas.size());
        cargarPregunta(preguntaActual);
    });

    connect(ui->pbResolverPreguntas, &QPushButton::clicked, this, &MainWindow::comprobarRespuestas);

    connect(ui->actionZoom_In, &QAction::triggered, this, &MainWindow::zoomIn);
    connect(ui->actionZoom_Out, &QAction::triggered, this, &MainWindow::zoomOut);
    connect(ui->actionMover_Regla, &QAction::triggered, this, &MainWindow::moverRegla);

    // Desactivadas hasta que se selecciona algo
    ui->actionRotar->setEnabled(false);
    connect(ui->actionRotar, &QAction::triggered, this, &MainWindow::rotacion);

    connect(scene, &QGraphicsScene::selectionChanged, this, &MainWindow::actualizarAcciones);

    connect(ui->actionLapiz, &QAction::triggered, this, &MainWindow::lapiz);
    connect(ui->actionRegla, &QAction::triggered, this, &MainWindow::regla);
    connect(ui->actionTransportador, &QAction::triggered, this, &MainWindow::transportador);
    connect(ui->actionCompas, &QAction::triggered, this, &MainWindow::compas);
    connect(ui->actionMi_Perfil, &QAction::triggered,this,&MainWindow::abrirPerfil);
    connect(ui->actionCerrar_Sesion, &QAction::triggered,this,&MainWindow::cerrarSesion);
    connect(ui->actionResetear, &QAction::triggered, this, &MainWindow::reset);
    connect(ui->actionTexto, &QAction::triggered, this, &MainWindow::texto);
    connect(ui->actionEstadisticas, &QAction::triggered, this, &MainWindow::estadisticas);

    connect(ui->sliderGrosor2, &QSlider::valueChanged, this, [=](int value){
        grosorLinea = value;
        if(lineaActual){
            QPen pen = lineaActual->pen();
            pen.setWidth(value);
            lineaActual->setPen(pen);
        }
    });

    connect(ui->botonColor2, &QPushButton::clicked, this, [=](){
        QColor color = QColorDialog::getColor(colorLinea, this);
        if (color.isValid()) {
            colorLinea = color;
            if(lineaActual){
                QPen pen = lineaActual->pen();
                pen.setColor(color);
                lineaActual->setPen(pen);
            }
        }
    });
    connect(ui->actionGoma, &QAction::triggered, this, &MainWindow::goma);

    connect(ui->cambiarColor, &QPushButton::clicked, this, [=](){
        QColor color = QColorDialog::getColor(colorTexto, this);
        if (color.isValid()){
            colorTexto = color;
            if(textoActual){

            }
        }
    });

    connect(ui->fontSize, &QComboBox::currentTextChanged, this, [=](const QString &size){
        if (textoActual) {
            QFont f = textoActual->font();
            f.setPointSize(size.toInt());
            textoActual->setFont(f);
        }
    });


    connect(ui->fontType, &QFontComboBox::currentFontChanged, this, [=](const QFont &font){
        if (textoActual) {
            QFont f = textoActual->font();
            f.setFamily(font.family());
            textoActual->setFont(f);
        }
    });


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
}

// ------- ACTUALIZACION DE MODOS ------------
void MainWindow::actualizarAcciones(){
    bool hay_seleccion = !scene->selectedItems().isEmpty();
    ui->actionRotar->setEnabled(hay_seleccion);
    // Obtenemos la lista una sola vez para que sea estable
    QList<QGraphicsItem*> seleccion = scene->selectedItems();

    if (seleccion.isEmpty()) {
        lineaActual = nullptr;
        textoActual = nullptr;
        ui->panelLapiz->hide();
        ui->panelTexto->hide();
        ui->actionRotar->setEnabled(false);
        return; // Salimos temprano si no hay nada
    }

    // Ahora es seguro usar seleccion.first()
    ui->actionRotar->setEnabled(true);

    QGraphicsItem* item = seleccion.first();

    // Usamos qgraphicsitem_cast que es más seguro y rápido que dynamic_cast en Qt
    QGraphicsLineItem* linea = qgraphicsitem_cast<QGraphicsLineItem*>(item);
    QGraphicsTextItem* texto = qgraphicsitem_cast<QGraphicsTextItem*>(item);

    if (linea) {
        lineaActual = linea;
        ui->panelLapiz->show();
        ui->panelTexto->hide();
        ui->sliderGrosor2->setValue(linea->pen().width());
        colorLinea = linea->pen().color();
    }
    else if (texto) {
        textoActual = texto;
        ui->panelLapiz->hide();
        ui->panelTexto->show();
        ui->fontType->setCurrentFont(texto->font());
        ui->fontSize->setCurrentText(QString::number(texto->font().pointSize()));
        colorTexto = texto->defaultTextColor();
    }
}

// --------- ROTACION --------------
void MainWindow::rotarSeleccion(int angulo)
{
    auto items = scene->selectedItems();
    if (items.isEmpty()) return;

    QGraphicsItem* item = items.first();

    if(item == pivotPoint) return;

    if(pivotPoint && pivotPoint->isVisible()) {
        QPointF pivotScenePos = pivotPoint->pos();
        QPointF itemPos = item->pos();
        QRectF rect = item->boundingRect();
        QPointF centerLocal = rect.center();
        QPointF centerScene = item->mapToScene(centerLocal);
        QPointF vec = centerScene - pivotScenePos;
        qreal rad = qDegreesToRadians((qreal)angulo);
        qreal cosA = qCos(rad);
        qreal sinA = qSin(rad);

        QPointF vecRotado(
            vec.x() * cosA - vec.y() * sinA,
            vec.x() * sinA + vec.y() * cosA
            );

        QPointF newCenterScene = pivotScenePos + vecRotado;
        QPointF desplazamiento = newCenterScene - centerScene;
        item->setPos(itemPos + desplazamiento);
        item->setRotation(item->rotation() + angulo);
    } else {
        item->setRotation(item->rotation() + angulo);
    }
}

void MainWindow::rotacion(){
    rotacionActiva = !rotacionActiva;

    auto items = scene->selectedItems();
    if(rotacionActiva){
        ui->actionRotar->setChecked(true);
        for(QGraphicsItem* item : std::as_const(items)){
            if(item != pivotPoint){
                item->setFlag(QGraphicsItem::ItemIsMovable, false);
            }
        }

        QPointF centroInicial;
        auto items = scene->selectedItems();

        if(!items.isEmpty() && items.first() != pivotPoint){
            QGraphicsItem* item = items.first();
            centroInicial = item->mapToScene(item->boundingRect().center());
        } else {
            centroInicial = view->mapToScene(view->viewport()->rect().center());
        }

        if(!pivotPoint){
            pivotPoint = scene->addEllipse(-10, -10, 20, 20,
                                           QPen(Qt::red, 2),
                                           QBrush(QColor(255, 0, 0, 150)));
            pivotPoint->setZValue(10000);
            pivotPoint->setFlag(QGraphicsItem::ItemIsMovable, true);
            pivotPoint->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pivotPoint->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
        }

        pivotPoint->setPos(centroInicial);
        pivotPoint->show();

    } else {
        ui->actionRotar->setText("Rotar");
        ui->actionRotar->setChecked(false);

        for(QGraphicsItem* item : std::as_const(items)){
            if(item != pivotPoint){
                if(dynamic_cast<QGraphicsLineItem*>(item) ||
                    dynamic_cast<QGraphicsEllipseItem*>(item) ||
                    dynamic_cast<QGraphicsTextItem*>(item) ||
                    dynamic_cast<QGraphicsSvgItem*>(item)){
                    item->setFlag(QGraphicsItem::ItemIsMovable, true);
                }
            }
        }
        if(pivotPoint){
            pivotPoint->hide();
        }
    }
}

// ------- HERRAMIENTAS -------------
QPointF MainWindow::posicionRaton(){
    QPoint posGlobal = QCursor::pos();
    QPoint posView = view->mapFromGlobal(posGlobal);
    return view->mapToScene(posView);

}

void MainWindow::regla() {
    setHerramienta(HerramientaActiva::Regla);
}
void MainWindow::transportador() {
    setHerramienta(HerramientaActiva::Transportador);
}
void MainWindow::compas() {
    setHerramienta(HerramientaActiva::Compas);
}

void MainWindow::lapiz() {
    setHerramienta(
        herramientaActual == HerramientaActiva::Lapiz
            ? HerramientaActiva::Ninguna
            : HerramientaActiva::Lapiz
        );
}

void MainWindow::goma(){
    setHerramienta(
        herramientaActual == HerramientaActiva::Goma
            ? HerramientaActiva::Ninguna
            : HerramientaActiva::Goma
        );
}

void MainWindow::texto(){
    setHerramienta(
        herramientaActual == HerramientaActiva::Texto
            ? HerramientaActiva::Ninguna
            : HerramientaActiva::Texto
        );
}

void MainWindow::setHerramienta(HerramientaActiva nueva)
{
    ui->panelLapiz->hide();
    ui->panelTexto->hide();
    view->viewport()->unsetCursor();

    herramientaActual = nueva;
    switch (nueva) {
    case HerramientaActiva::Lapiz:
        ui->panelLapiz->show();
        view->viewport()->setCursor(QCursor(QPixmap(":/icons/icons/pencil.png").scaled(24,24)));
        break;

    case HerramientaActiva::Goma:
        view->viewport()->setCursor(QCursor(QPixmap(":/icons/icons/eraser.png").scaled(24,24)));
        break;

    case HerramientaActiva::Texto:
        ui->panelTexto->show();
        view->viewport()->setCursor(QCursor(QPixmap(":/icons/icons/text.png").scaled(24,24)));
        break;

    case HerramientaActiva::Regla:
        if (!reglaActiva){
            reglaActual = new QGraphicsSvgItem(":/icons/icons/ruler2.svg");
            ponerSvg(reglaActual, 2);
            reglaActual->setPos(scene->sceneRect().center() - reglaActual->boundingRect().center());
            reglaActiva = true;
            ui->actionMover_Regla->setEnabled(true);
        }
        else{
            scene->removeItem(reglaActual);
            delete reglaActual;
            reglaActual = nullptr;
            herramientaActual = HerramientaActiva::Ninguna;
            view->viewport()->unsetCursor();
            reglaActiva = false;
            ui->actionMover_Regla->setEnabled(false);
        }
        break;

    case HerramientaActiva::Compas:
        if(!compasActivo){
            compasActual = new QGraphicsSvgItem(":/icons/icons/compass_leg.svg");
            ponerSvg(compasActual, 2);
            compasActual->setPos(scene->sceneRect().center() - compasActual->boundingRect().center());
            compasActivo = true;
        }
        else{
            scene->removeItem(compasActual);
            delete compasActual;
            compasActual = nullptr;
            herramientaActual = HerramientaActiva::Ninguna;
            view->viewport()->unsetCursor();
            compasActivo = false;
        }
        break;

    case HerramientaActiva::Transportador:
        if(!transportadorActivo){
            transportadorActual = new QGraphicsSvgItem(":/icons/icons/transportador.svg");
            ponerSvg(transportadorActual, 1.5);
            transportadorActual->setPos(scene->sceneRect().center() - transportadorActual->boundingRect().center());
            transportadorActivo = true;
        }
        else{
            scene->removeItem(transportadorActual);
            delete transportadorActual;
            transportadorActual = nullptr;
            herramientaActual = HerramientaActiva::Ninguna;
            view->viewport()->unsetCursor();
            transportadorActivo = false;
        }
        break;

    case HerramientaActiva::Ninguna:
        view->viewport()->unsetCursor();
        break;
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
    Perfil ventanaPerfil(m_user, this);
    if (ventanaPerfil.exec() == QDialog::Accepted) {
        // Opcional: Si el usuario cambió su avatar o nombre,
        // podrías refrescar algún label de la MainWindow aquí.
        qDebug() << "Cambios guardados y volviendo al mapa...";
    }
}

void MainWindow::cerrarSesion(){
    sesion= Session(QDateTime::currentDateTime(), aciertos, fallos);
    Navigation::instance().addSession(m_user->nickName(), sesion);
    aciertos = 0;
    fallos = 0;
    LoginRegister *login = new LoginRegister();
    login->show();
    login->mostrarLogin();
    this->close();
}


// ------------------ RESET ---------------
void MainWindow::reset(){
    scene->clear();
    herramientaActual = HerramientaActiva::Ninguna;

    reglaActual = nullptr;
    transportadorActual = nullptr;
    compasActual = nullptr;
    lineaActual = nullptr;
    textoActual = nullptr;

    ui->panelLapiz->hide();
    ui->panelTexto->hide();

    QPixmap pm(":/icons/icons/carta_nautica.jpg");
    QGraphicsPixmapItem *item = scene->addPixmap(pm);
    item->setZValue(0);

    escalado = 0.2;
    view->resetTransform();
    view->scale(escalado, escalado);
    view->viewport()->unsetCursor();
}


void MainWindow::salirModoTexto(){
    textoActual = nullptr;
    view->viewport()->unsetCursor();
    ui->panelTexto->hide();
}

// Para poder hacer zoom con el ratón
bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    // ZOOM y ROTACION
    if (obj == view->viewport() && event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);

        // CTRL + Scroll = Zoom
        if (wheelEvent->modifiers() & Qt::CTRL) {
            double factor = 1.15;
            if (wheelEvent->angleDelta().y() > 0)
                applyZoom(factor);
            else
                applyZoom(1.0 / factor);
            return true;
        }
        // Shift + Scroll = Rotación
        else if((wheelEvent->modifiers() & Qt::ShiftModifier) && rotacionActiva){
            int delta = wheelEvent->angleDelta().y();
            int angulo = (delta > 0) ? 5 : -5;
            auto items = scene->selectedItems();
            if(!items.isEmpty()){
                rotarSeleccion(angulo);
                return true;
            }
        }
    }

    // LINEAS
    if (obj == view->viewport() && (herramientaActual == HerramientaActiva::Lapiz)){
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
                    lineaActual = new QGraphicsLineItem(QLineF(inicioLinea, posActual));

                    QPen pen(colorLinea, grosorLinea);
                    lineaActual->setPen(pen);

                    lineaActual->setFlag(QGraphicsItem::ItemIsMovable);
                    lineaActual->setFlag(QGraphicsItem::ItemIsSelectable);
                    lineaActual->setFlag(QGraphicsItem::ItemIsFocusable);

                    scene->addItem(lineaActual);
                } else {
                    lineaActual->setLine(QLineF(inicioLinea, posActual));
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

    // GOMA
    if (obj == view->viewport() && (herramientaActual == HerramientaActiva::Goma)) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {

                QPointF pos = view->mapToScene(mouseEvent->pos());
                QList<QGraphicsItem*> items = scene->items(pos);

                for (QGraphicsItem* item : std::as_const(items)) {
                    // No borrar el pivote
                    if(item == pivotPoint) continue;

                    if (auto linea = dynamic_cast<QGraphicsLineItem*>(item)) {
                        if (linea == lineaActual)
                            lineaActual = nullptr;
                        scene->removeItem(linea);
                        delete linea;
                        break;
                    }
                    else if (auto punto = dynamic_cast<QGraphicsEllipseItem*>(item)) {
                        scene->removeItem(punto);
                        delete punto;
                        break;
                    }
                }
            }
            return true;
        }
    }

    // TEXTO
    if (obj == view->viewport() && (herramientaActual == HerramientaActiva::Texto)) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                QPointF pos = view->mapToScene(mouseEvent->pos());

                EditableTextItem* textoItem = new EditableTextItem(this);
                scene->addItem(textoItem);

                QFont font;
                font.setPointSize(ui->fontSize->currentText().toInt());
                font.setFamily(ui->fontType->currentFont().family());

                textoItem->setFont(font);
                textoItem->setDefaultTextColor(colorTexto);
                textoItem->setPos(pos);
                textoItem->setFlag(QGraphicsItem::ItemIsMovable);
                textoItem->setFlag(QGraphicsItem::ItemIsSelectable);
                textoItem->setFlag(QGraphicsItem::ItemIsFocusable);

                textoItem->setTextInteractionFlags(Qt::TextEditorInteraction);
                textoItem->setFocus();
            }
            return true;
        }
    }

    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::estadisticas() {
    // Si m_user es nulo por algún error previo, evitamos el crash aquí
    if (!m_user) {
        QMessageBox::critical(this, "Error", "No hay un usuario cargado.");
        return;
    }

    stats *Stats = new stats(m_user, &sesion, this);
    Stats->show();
}

//---------Preguntas----------
void MainWindow::cargarPregunta(int index){

    if (listaPreguntas.isEmpty())return;
    if(index < 0 || index >= listaPreguntas.size()) return;



    const Problem &p = listaPreguntas[index];

    ui->lIndice->setText(QString("Pregunta %1 / %2").arg(index+1).arg(listaPreguntas.size()));

    ui->lPregunta->setWordWrap(true);
    ui->lPregunta->setText(p.text());

    const auto &a = p.answers();
    if(a.size() < 4) return;

    QRadioButton *btns[4] {ui->rb1, ui->rb2, ui->rb3,  ui->rb4};

    for(int i = 0; i < 4; i++){
        btns[i]->setText(a[i].text());
        btns[i]->setProperty("correcta", a[i].validity());
    }

    aplicarEstadoPregunta(index);
    /*ui->rb1->setChecked(false);
    ui->rb2->setChecked(false);
    ui->rb3->setChecked(false);
    ui->rb4->setChecked(false);

    ui->rb1->setAutoExclusive(true);
    ui->rb2->setAutoExclusive(true);
    ui->rb3->setAutoExclusive(true);
    ui->rb4->setAutoExclusive(true);*/
}

void MainWindow::toggleDockPreguntas()
{
    if (dockExpandido) {
        // Colapsar
        ui->dockWidget->setMinimumWidth(30);
        ui->dockWidget->setMaximumWidth(30);
        ui->pbTogglePreguntas->setText("⮞");
        dockExpandido = false;
        ui->lPregunta->setVisible(false);
        ui->lIndice->setVisible(false);
        ui->rb1->setVisible(false);
        ui->rb2->setVisible(false);
        ui->rb3->setVisible(false);
        ui->rb4->setVisible(false);
        ui->pbSiguiente->setVisible(false);
        ui->pbRandom->setVisible(false);
        ui->pbAnterior->setVisible(false);
        ui->pbResolverPreguntas->setVisible(false);
    } else {
        // Expandir
        ui->dockWidget->setMinimumWidth(dockWidthExpandido);
        ui->dockWidget->setMaximumWidth(dockWidthExpandido);
        ui->pbTogglePreguntas->setText("⮜");
        dockExpandido = true;
        ui->lPregunta->setVisible(true);
        ui->lIndice->setVisible(true);
        ui->rb1->setVisible(true);
        ui->rb2->setVisible(true);
        ui->rb3->setVisible(true);
        ui->rb4->setVisible(true);
        ui->pbSiguiente->setVisible(true);
        ui->pbRandom->setVisible(true);
        ui->pbAnterior->setVisible(true);
        ui->pbResolverPreguntas->setVisible(true);
    }
}

void MainWindow::comprobarRespuestas(){
    if(preguntaActual < 0 || preguntaActual >= listaPreguntas.size()) return;

    if(preguntaActual < estadosPreguntas.size() && estadosPreguntas[preguntaActual].respondida){
        aplicarEstadoPregunta(preguntaActual);
        return;
    }

    QRadioButton *btns[4] {ui->rb1, ui->rb2, ui->rb3,  ui->rb4};

    int indexSeleccion = -1;

    for(int i = 0; i < 4; i++){
        if(btns[i]->isChecked()){
            indexSeleccion = i;
            break;
        }
    }

    if(indexSeleccion == -1){
        QMessageBox::warning(this, "Atención", "Seleccione una respuesta primero");
        return;
    }

    int indexCorrecta = -1;

    for(int i = 0; i < 4; i++){
        if(btns[i]->property("correcta").toBool()){
            indexCorrecta = i;
            break;
        }
    }

    const bool acierto = btns[indexSeleccion]->property("correcta").toBool();

    if(estadosPreguntas.size() != listaPreguntas.size()){
        estadosPreguntas.resize(listaPreguntas.size());
    }

    auto &st = estadosPreguntas[preguntaActual];

    st.respondida = true;
    st.seleccion = indexSeleccion;
    st.correcta = indexCorrecta;
    st.acierto = acierto;

    preguntasRespondidas.insert(preguntaActual);

    if(acierto){
        aciertos++;
    }else{
        fallos++;
    }

    aplicarEstadoPregunta(preguntaActual);
}


void MainWindow::aplicarEstadoPregunta(int index){
    if(index < 0 || index >= listaPreguntas.size()) return;

    const QString estiloNormal = "background-color : #C7DCE8";
    const QString estiloCorrecta = "background-color : green";
    const QString estiloFallada = "background-color : red";

    QRadioButton *btns[4] = { ui->rb1, ui->rb2, ui->rb3, ui->rb4 };

    for(int i = 0; i < 4; i++){
        btns[i]->setStyleSheet(estiloNormal);
        btns[i]->setEnabled(true);

        btns[i]->setAutoExclusive(false);
        btns[i]->setChecked(false);
        btns[i]->setAutoExclusive(true);
    }

    ui->pbResolverPreguntas->setEnabled(true);

    if(index >= estadosPreguntas.size()) return;

    const auto &st = estadosPreguntas[index];

    if(!st.respondida) return;

    if(st.seleccion >= 0 && st.seleccion < 4){
        btns[st.seleccion]->setChecked(true);
        btns[st.seleccion]->setStyleSheet(st.acierto ? estiloCorrecta : estiloFallada);
    }

    if(!st.acierto && st.correcta >= 0 && st.correcta < 4){
        btns[st.correcta]->setStyleSheet(estiloCorrecta);
    }

    for(int i = 0; i < 4; i++){
        btns[i]->setEnabled(false);
    }

    ui->pbResolverPreguntas->setEnabled(false);
}


void MainWindow::moverRegla() {
    if (!reglaActual || !reglaActiva) return;

    // --- VALORES A AJUSTAR (Prueba hasta que cuadre con tu mapa) ---
    const QPointF posicionMapa(8200, 3800); // Cambia estos números (X, Y)
    const qreal anguloVertical = -90.0;       // Cambia esto (0, 90, 180, etc.)
    // --------------------------------------------------------------

    if (!reglaApartada) {
        // 1. Guardar estado actual (Posición y Rotación)
        posicionOriginalRegla = reglaActual->pos();
        rotacionOriginalRegla = reglaActual->rotation();

        // 2. Mover y "poner de pie"
        reglaActual->setRotation(anguloVertical);
        reglaActual->setPos(posicionMapa);

        reglaApartada = true;
    } else {
        // 3. Volver a como estaba antes
        reglaActual->setRotation(rotacionOriginalRegla);
        reglaActual->setPos(posicionOriginalRegla);

        reglaApartada = false;
    }
}
