#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QIcon>
#include <QSqlDatabase>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QLabel>
#include <QDebug>
#include <QDesktopServices>
#include <QPainter>
#include <QPdfWriter>
#include <QDir>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("INNOSTAY");
    ui->table_Clients->setModel(C.afficher());
    ui->table_Clients->setColumnWidth(3, 250);
    ui->comboBox_IDs->setModel(C.afficher_cin());
    ui->line_ID->setValidator( new QIntValidator(0, 99999999, this));
    ui->line_numtel->setValidator( new QIntValidator(0, 99999999, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bt_ajouter_clicked()
{
    int CIN = ui->line_ID->text().toInt();
    QString NOM = ui->line_nom->text();
    QString PRENOM = ui->line_prenom->text();
    QString EMAIL = ui->line_email->text();
    int NUMTEL = ui->line_numtel->text().toInt();

    QString CIN_String = ui->line_ID->text();
    QString NUMTEL_String = ui->line_numtel->text();
    if(NUMTEL_String.isEmpty()||EMAIL.isEmpty()||CIN_String.isEmpty()||CIN == 0||NOM.isEmpty()||PRENOM.isEmpty()){
        ui->label_info_gestion->setText("Erreur de controle de saisire");
        return;
    }

    Client C(CIN,NOM,PRENOM,EMAIL,NUMTEL);
    bool test = C.ajouter();
    if(test){
        ui->label_info_gestion->setText("Ajout Effectué CIN: "+CIN);
        ui->table_Clients->setModel(C.afficher());
        ui->comboBox_IDs->setModel(C.afficher_cin());
    }else{
        ui->label_info_gestion->setText("ajout non effectué");
    }
}

void MainWindow::on_bt_modifier_clicked()
{
    int CIN = ui->line_ID->text().toInt();
    QString NOM = ui->line_nom->text();
    QString PRENOM = ui->line_prenom->text();
    QString EMAIL = ui->line_email->text();
    int NUMTEL = ui->line_numtel->text().toInt();
    QString CIN_String = ui->line_ID->text();
    QString NUMTEL_String = ui->line_numtel->text();
    if(NUMTEL_String.isEmpty()||EMAIL.isEmpty()||CIN_String.isEmpty()||CIN == 0||NOM.isEmpty()||PRENOM.isEmpty()){
        ui->label_info_gestion->setText("Erreur de controle de saisire");
        return;
    }
    Client C(CIN,NOM,PRENOM,EMAIL,NUMTEL);
    bool test = C.modifier();
    if(test){
        ui->label_info_gestion->setText("Modification Effectué CIN: "+CIN);
        ui->table_Clients->setModel(C.afficher());
        ui->comboBox_IDs->setModel(C.afficher_cin());
    }else{
        ui->label_info_gestion->setText("Modification non effectué");
    }
}

void MainWindow::on_bt_supprimer_clicked()
{
    Client C;
    C.setCIN(ui->comboBox_IDs->currentText().toInt());
    bool test=C.supprimer(C.getCIN());
    if(test)
    {
        ui->label_info_gestion->setText("Suppression Effectué");
        ui->table_Clients->setModel(C.afficher());
        ui->comboBox_IDs->setModel(C.afficher_cin());
    }
    else
    {
        ui->label_info_gestion->setText("Suppression non effectué");
    }
}

void MainWindow::on_comboBox_IDs_currentIndexChanged(int index)
{
    int CIN = ui->comboBox_IDs->currentText().toInt();
    QString CIN_1=QString::number(CIN);
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT where CIN='"+CIN_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->line_ID->setText(query.value(0).toString());
            ui->line_nom->setText(query.value(1).toString());
            ui->line_prenom->setText(query.value(2).toString());
            ui->line_email->setText(query.value(3).toString());
            ui->line_numtel->setText(query.value(4).toString());
        }
    }
    else
    {
        ui->label_info_gestion->setText("Echec de chargement");
    }
}

void MainWindow::on_line_Recherche_textChanged(const QString &arg1)
{
    C.clearTable(ui->table_Clients);
    C.rechercher(ui->table_Clients,arg1);
    ui->table_Clients->setColumnWidth(3, 250);
}

void MainWindow::on_bt_Tri_Nom_clicked()
{
    ui->label_info_gestion->setText("Tri par NOM effectué");
    ui->table_Clients->setModel(C.tri_Nom());
}


void MainWindow::on_bt_Tri_CIN_clicked()
{
    ui->label_info_gestion->setText("Tri par CIN effectué");
    ui->table_Clients->setModel(C.tri_CIN());
}

void MainWindow::on_bt_ExportPDF_clicked()
{
    QString currentPath = QDir::currentPath();
    QString pdfPath = currentPath + "/Liste-Client.pdf";
    QString logoPath = currentPath + "/ressource/Logo.png";
    QPdfWriter pdf(pdfPath);
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30));
    painter.drawPixmap(QRect(100,400,2000,2000),QPixmap(logoPath));
    painter.drawText(3000,1500,"LISTE DES CLIENTS");
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 50));
    painter.drawRect(2700,200,7000,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300, 3300, "CIN");
    painter.drawText(1300, 3300, "Nom");
    painter.drawText(2000, 3300, "Prenom");
    painter.drawText(4000, 3300, "Email");
    painter.drawText(6800, 3300, "N° Tel");
    QSqlQuery query;
    query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti=localtime(&tt);
    asctime(ti);
    painter.drawText(500,300, asctime(ti));
    query.prepare("select * from CLIENT");
    query.exec();
    while (query.next())
    {
        painter.drawText(300, i, query.value(0).toString());
        painter.drawText(1300, i, query.value(1).toString());
        painter.drawText(2000, i, query.value(2).toString());
        painter.drawText(4000, i, query.value(3).toString());
        painter.drawText(6800, i, query.value(4).toString());
        i = i +500;
    }
    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(pdfPath));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }

}
