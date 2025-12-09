#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login_register.h"
#include "navigation.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::applyZoom(double factor){
    // factor > 1 acerca, factor < 1 aleja
    double newScale = escalado * factor;
    const double minScale = 0.1;
    const double maxScale = 1;

    if (newScale < minScale){
        factor = minScale / escalado;
        newScale = maxScale;
    }
    else if (newScale > maxScale){
        factor = maxScale / escalado;
        newScale = maxScale;
    }
    view->scale(factor, factor);
    escalado = newScale;
}
