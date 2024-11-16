#include "dialog_statistiques.h"
#include "ui_dialog_statistiques.h"
#include "employe.h"
#include "mainwindow.h"

Dialog_Statistiques::Dialog_Statistiques(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Statistiques)
{
    ui->setupUi(this);
}

Dialog_Statistiques::~Dialog_Statistiques()
{
    delete ui;
}

void Dialog_Statistiques::choix_pie()
{
    QSqlQuery q1,q2,q3,q4,q5,q6,q7;
    qreal tot=0,c1=0,c2=0,c3=0,c4=0,c5=0,c6=0;
    q1.prepare("SELECT * FROM EMPLOYE");
    q1.exec();
    q2.prepare("SELECT * FROM EMPLOYE WHERE GESTION='Gestion des employe';");
    q2.exec();
    q3.prepare("SELECT * FROM EMPLOYE WHERE GESTION='Gestion des clients';");
    q3.exec();
    q4.prepare("SELECT * FROM EMPLOYE WHERE GESTION='Gestion des reservation'");
    q4.exec();
    q5.prepare("SELECT * FROM EMPLOYE WHERE GESTION='Gestion d'animation'");
    q5.exec();
    q6.prepare("SELECT * FROM EMPLOYE WHERE GESTION='Gestion de restauration'");
    q6.exec();
    q7.prepare("SELECT * FROM EMPLOYE WHERE GESTION='Gestion d'equipement'");
    q7.exec();
    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}
    while (q5.next()){c4++;}
    while (q6.next()){c5++;}
    while (q7.next()){c6++;}
    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;
    c4=c4/tot;
    c5=c5/tot;
    c6=c6/tot;
    QPieSeries *series = new QPieSeries();
    series->append("G.Employes",c1);
    series->append("G.Clients",c2);
    series->append("G.Res",c3);
    series->append("G.Anim",c4);
    series->append("G.Res",c5);
    series->append("G.Equip",c6);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->show();
    chartView = new QChartView(chart,ui->label_stats);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(500,500);
    chartView->show();
}

void Dialog_Statistiques::on_pushButton_Fermer_clicked()
{
    close();
}
