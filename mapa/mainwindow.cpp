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
    connect(ui->label_10, &ClickableLabel::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->page_2);


    });
    connect(ui->checkBox_2, &QCheckBox::toggled, this, [this](bool checked) {
        if (checked) {
            ui->lineEdit_6->setEchoMode(QLineEdit::Normal);
        } else {
            ui->lineEdit_6->setEchoMode(QLineEdit::Password);
        }
    });
    connect(ui->checkBox_3, &QCheckBox::toggled, this, [this](bool checked) {
        if (checked) {
            ui->lineEdit_3->setEchoMode(QLineEdit::Normal);
        } else {
            ui->lineEdit_3->setEchoMode(QLineEdit::Password);
        }
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
