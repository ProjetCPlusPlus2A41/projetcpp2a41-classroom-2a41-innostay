#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
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
#include "smtp.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("INNOSTAY");
    ui->table_Employe->setModel(E.afficher());
    ui->comboBox_IDs->setModel(E.afficher_cin());
    ui->Login_CIN_Filed->setValidator( new QIntValidator(0, 99999999, this));
    ui->line_ID->setValidator( new QIntValidator(0, 99999999, this));
    ui->line_numtel->setValidator( new QIntValidator(0, 99999999, this));
    // ui->line_salaire->setValidator( new QIntValidator(0, 99999999, this));
    ui->line_salaire->setValidator(new QDoubleValidator(0, 99999999, 2, this));
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow() {
    delete ui;
}

int modes=1;
void MainWindow::on_Login_check_PassShowHide_clicked()
{
    if(modes==1){
        ui->Login_MDP_Field->setEchoMode(QLineEdit::Normal);modes=0;
    }
    else{
        ui->Login_MDP_Field->setEchoMode(QLineEdit::Password);modes=1;
    }
}

void MainWindow::on_Login_Button_clicked()
{
    QString CIN = ui->Login_CIN_Filed->text();
    QString PASSWORD = ui->Login_MDP_Field->text();
    QSqlQuery query;
    QString gestion;
    if(query.exec("SELECT * FROM EMPLOYE WHERE CIN='" + CIN + "' AND PASSWORD='" + PASSWORD + "'")) {
        if (query.next()) {
            //gestion = query.value(9).toString();
            ui->stackedWidget->setCurrentIndex(1);
        }
        else {
            ui->label_infoconx->setText("CIN ou Password sont incorrects");
        }
    }
}


void MainWindow::on_bt_ajouter_clicked()
{
    int CIN = ui->line_ID->text().toInt();
    QString NOM = ui->line_nom->text();
    QString PRENOM = ui->line_prenom->text();
    QDate DATE_NAISSANCE = ui->date_ddn->date();
    QString VILLE = ui->line_ville->text();
    QString GESTION = ui->comboBox_Gestion->currentText();
    QString PASSWORD = ui->line_password->text();
    QDate DATE_EMBAUCHE = ui->date_emb->date();
    int SALAIRE = ui->line_salaire->text().toInt();
    int NUM_TEL = ui->line_numtel->text().toInt();

    QString SALAIRE_String = ui->line_salaire->text();
    QString CIN_String = ui->line_ID->text();
    QString NUM_TEL_String = ui->line_numtel->text();
    if(NUM_TEL_String.isEmpty()||SALAIRE_String.isEmpty()||GESTION.isEmpty()||CIN_String.isEmpty()||CIN == 0||PASSWORD.isEmpty()||NOM.isEmpty()||PRENOM.isEmpty()||VILLE.isEmpty()){
        ui->label_info_gestion->setText("Erreur de controle de saisire");
        return;
    }

    EMPLOYE E(CIN,NOM,PRENOM,DATE_NAISSANCE,VILLE,PASSWORD,DATE_EMBAUCHE,SALAIRE,NUM_TEL,GESTION);
    bool test = E.ajouter();
    if(test){
        ui->label_info_gestion->setText("Ajout Effectué");
        ui->table_Employe->setModel(E.afficher());
        ui->comboBox_IDs->setModel(E.afficher_cin());
    }else{
        ui->label_info_gestion->setText("Ajout non effectué");
    }
}

void MainWindow::on_bt_modifier_clicked()
{
    int CIN = ui->line_ID->text().toInt();
    QString NOM = ui->line_nom->text();
    QString PRENOM = ui->line_prenom->text();
    QDate DATE_NAISSANCE = ui->date_ddn->date();
    QString VILLE = ui->line_ville->text();
    QString GESTION = ui->comboBox_Gestion->currentText();
    QString PASSWORD = ui->line_password->text();
    QDate DATE_EMBAUCHE = ui->date_emb->date();
    int SALAIRE = ui->line_salaire->text().toInt();
    int NUM_TEL = ui->line_numtel->text().toInt();
    QString SALAIRE_String = ui->line_salaire->text();
    QString CIN_String = ui->line_ID->text();
    QString NUM_TEL_String = ui->line_numtel->text();
    if(NUM_TEL_String.isEmpty()||SALAIRE_String.isEmpty()||GESTION.isEmpty()||CIN_String.isEmpty()||CIN == 0||PASSWORD.isEmpty()||NOM.isEmpty()||PRENOM.isEmpty()||VILLE.isEmpty()){
        ui->label_info_gestion->setText("Erreur de controle de saisire");
        return;
    }
    EMPLOYE E(CIN,NOM,PRENOM,DATE_NAISSANCE,VILLE,PASSWORD,DATE_EMBAUCHE,SALAIRE,NUM_TEL,GESTION);
    bool test = E.modifier();
    if(test){
        ui->label_info_gestion->setText("Modification Effectué");
        ui->table_Employe->setModel(E.afficher());
        ui->comboBox_IDs->setModel(E.afficher_cin());
    }else{
        ui->label_info_gestion->setText("Modification effectué");
    }
}

void MainWindow::on_bt_supprimer_clicked()
{
    EMPLOYE E;
    E.setCIN_EMPLOYE(ui->comboBox_IDs->currentText().toInt());
    bool test=E.supprimer(E.getCIN_EMPLOYE());
    if(test)
    {
        ui->label_info_gestion->setText("Suppression Effectué");
        ui->table_Employe->setModel(E.afficher());
        ui->comboBox_IDs->setModel(E.afficher_cin());
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
    query.prepare("SELECT * FROM EMPLOYE where CIN='"+CIN_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->line_ID->setText(query.value(0).toString());
            ui->line_nom->setText(query.value(1).toString());
            ui->line_prenom->setText(query.value(2).toString());
            ui->date_ddn->setDate(query.value(3).toDate());
            ui->line_ville->setText(query.value(4).toString());
            ui->line_password->setText(query.value(5).toString());
            ui->date_emb->setDate(query.value(6).toDate());
            ui->line_salaire->setText(query.value(7).toString());
            ui->line_numtel->setText(query.value(8).toString());
            ui->comboBox_Gestion->setCurrentText(query.value(9).toString());
        }
    }
    else
    {
        ui->label_info_gestion  ->setText("Echec de chargement");
    }
}

void MainWindow::on_bt_Tri_Nom_clicked()
{
    ui->label_info_affichage->setText("Tri par NOM effectué");
    ui->table_Employe->setModel(E.tri_Nom());
}

void MainWindow::on_bt_Tri_Gestion_clicked()
{
    ui->label_info_affichage->setText("Tri par GESTION effectué");
    ui->table_Employe->setModel(E.tri_Gestion());
}

void MainWindow::on_bt_Tri_CIN_clicked()
{
    ui->label_info_affichage->setText("Tri par CIN effectué");
    ui->table_Employe->setModel(E.tri_CIN());
}


void MainWindow::on_line_Recherche_textChanged(const QString &arg1)
{
    E.clearTable(ui->table_Employe);
    E.rechercher(ui->table_Employe,arg1);
}

void MainWindow::on_bt_ExportPDF_clicked()
{
    QString currentPath = QDir::currentPath();
    QString pdfPath = currentPath + "/Liste-Employees.pdf";
    QString logoPath = currentPath + "/ressource/Logo.png";
    QPdfWriter pdf(pdfPath);
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30));
    painter.drawPixmap(QRect(100,400,2000,2000),QPixmap(logoPath));
    painter.drawText(3000,1500,"LISTE DES EMPLOYÉS");
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 50));
    painter.drawRect(2700,200,7000,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300, 3300, "CIN");
    painter.drawText(1300, 3300, "Nom");
    painter.drawText(2000, 3300, "Prenom");
    painter.drawText(3000, 3300, "DDN");
    painter.drawText(4000, 3300, "Ville");
    painter.drawText(4600, 3300, "Password");
    painter.drawText(5500, 3300, "Date Embauche");
    painter.drawText(6800, 3300, "Salaire");
    painter.drawText(7500, 3300, "N° Tel");
    painter.drawText(8500, 3300, "Gestion");
    QSqlQuery query;
    query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti=localtime(&tt);
    asctime(ti);
    painter.drawText(500,300, asctime(ti));
    query.prepare("select * from EMPLOYE");
    query.exec();
    while (query.next())
    {
        painter.drawText(300, i, query.value(0).toString());
        painter.drawText(1300, i, query.value(1).toString());
        painter.drawText(2000, i, query.value(2).toString());
        painter.drawText(2900, i, query.value(3).toDate().toString("dd/MM/yyyy"));
        painter.drawText(4000, i, query.value(4).toString());
        painter.drawText(4800, i, query.value(5).toString());
        painter.drawText(5600, i, query.value(6).toDate().toString("dd/MM/yyyy"));
        painter.drawText(6800, i, query.value(7).toString());
        painter.drawText(7300, i, query.value(8).toString());
        painter.drawText(8200, i, query.value(9).toString());
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

void MainWindow::on_Menu_Employes_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_return1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_Login_ResetPass_clicked()
{
    RP = new Resetpass();
    RP->setWindowTitle("Reset Password");
    RP->show();
}
