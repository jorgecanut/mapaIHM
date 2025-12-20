#include "stats.h"
#include "ui_stats.h"

stats::stats(User *user,Session *sesion, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::stats)
    , m_user(user)
    , m_sesion(sesion)
{
    ui->setupUi(this);

    QDate hoy = QDate::currentDate();
    ui->deFechaInicio->setCalendarPopup(true);
    ui->deFechaFinal->setCalendarPopup(true);

    ui->deFechaInicio->setDate(hoy.addDays(-7));
    ui->deFechaFinal->setDate(hoy);

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

    QMap<QDate, statsDia> porDia;

    int totalHits = 0;
    int totalFaults = 0;

    for(const Session &s : m_user->sessions()){
        const QDate d = s.timeStamp().date();

        if(d < inicio) continue;
        if(d > fin) continue;

        auto &st = porDia[d];
        st.sesiones++;
        st.hits += s.hits();
        st.faults += s.faults();

        totalHits += s.hits();
        totalFaults += s.faults();
    }

    QList<QDate> fechas = porDia.keys();
    std::sort(fechas.begin(), fechas.end(), std::greater<QDate>());

    ui->tableWidget->setRowCount(fechas.size());

    for(int row = 0; row < fechas.size(); row++){
        const QDate d = fechas[row];
        const statsDia &st = porDia[d];

        int total = st.hits + st.faults;
        double pct = (total == 0) ? 0.0 : (100 * st.hits / total);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(d.toString("dd/MM/yyyy")));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(st.sesiones)));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(st.hits)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(st.faults)));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(pct, 'f', 1) +"%"));
    }
}

void stats::ajustarRango(){
    QDate ini = ui->deFechaInicio->date();
    QDate fin = ui->deFechaFinal->date();

    if(fin < ini){
        ui->deFechaFinal->setDate(ini);
    }
}
