#include "stats.h"
#include "ui_stats.h"

stats::stats(User *user,Session *sesion, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::stats)
    , m_user(user)
    , m_sesion(sesion)
{
    ui->setupUi(this);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QDate hoy = QDate::currentDate();
    ui->deFechaInicio->setCalendarPopup(true);
    ui->deFechaFinal->setCalendarPopup(true);

    ui->deFechaInicio->setDate(hoy.addDays(-7));
    ui->deFechaFinal->setDate(hoy);

    connect(ui->btnVolver, &QPushButton::clicked, this, &stats::on_btnVolver_clicked);


    connect(ui->deFechaInicio, &QDateEdit::dateChanged, this, [this](const QDate&){
        ajustarRango();
        refrescarRango(ui->deFechaInicio->date(), ui->deFechaFinal->date());
    });

    connect(ui->deFechaFinal, &QDateEdit::dateChanged, this, [this](const QDate&){
        ajustarRango();
        refrescarRango(ui->deFechaInicio->date(), ui->deFechaFinal->date());
    });

    refrescarRango(ui->deFechaInicio->date(), ui->deFechaFinal->date());
}

stats::~stats()
{
    delete ui;
}

void stats::refrescarRango(const QDate &inicio, const QDate &fin){
    if(!m_user) return;

    ui->tableWidget->setRowCount(0);

    const auto &hist = m_user->sessions();

    int row = 0;
    for(const Session &s : hist){
        QDate d = s.timeStamp().date();
        if(d < inicio || d > fin) continue;

        int hits = s.hits();
        int faults = s.faults();
        int total = hits + faults;
        double percentage = (total == 0) ? 0.0 : (100.0 * hits /total);

        if(total != 0){
        ui->tableWidget->insertRow(row);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(s.timeStamp().toString("dd/MM/yyyy HH:mm")));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(hits)));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(faults)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(percentage, 'f', 1) + " %"));

        row++;
        }
    }
}

void stats::ajustarRango(){
    QDate ini = ui->deFechaInicio->date();
    QDate fin = ui->deFechaFinal->date();

    if(fin < ini){
        ui->deFechaFinal->setDate(ini);
    }
}
void stats::on_btnVolver_clicked()
{

    if(parentWidget()){
        parentWidget()->show();
    }

    this->close();
}
