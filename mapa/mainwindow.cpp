#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login_register.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Conecta el click de label_3 para cambiar de página
    connect(ui->label_3, &ClickableLabel::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->page);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
