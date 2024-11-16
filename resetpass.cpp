#include "resetpass.h"
#include "ui_resetpass.h"
#include "smtp.h"
#include <random>
#include <QSqlQuery>
#include <QString>
Resetpass::Resetpass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Resetpass)
{
    ui->setupUi(this);
    ui->line_CIN->setValidator( new QIntValidator(0, 99999999, this));
    ui->label2->setVisible(false);
    ui->label3->setVisible(false);
    ui->line_OTP->setVisible(false);
    ui->line_Pass->setVisible(false);
    ui->Confirmer->setVisible(false);
}

Resetpass::~Resetpass()
{
    delete ui;
}
QString CIN;
QString currentOtp;
void Resetpass::on_SendOTP_clicked()
{
    QString status;
    Smtp* smtp = new Smtp("smarteventoplanner@gmail.com", "okgxvskpbwjzyocr", "smtp.gmail.com", 465); // smtp.gmail.com
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(100000, 999999);
    QString otp = QString::number(dis(gen));
    currentOtp = otp;
    QSqlQuery query;
    CIN = ui->line_CIN->text();
    query.prepare("SELECT * FROM EMPLOYE WHERE CIN = :cin");
    query.bindValue(":cin", CIN);
    if(query.exec()) {
        if (query.next()) {
            smtp->sendMail("smarteventoplanner@gmail.com", ui->line_Email->text(),
                                       "Code OTP: "+otp,
                                       "Votre OTP code : "+otp);
            ui->label2->setVisible(true);
            ui->label3->setVisible(true);
            ui->line_OTP->setVisible(true);
            ui->line_Pass->setVisible(true);
            ui->Confirmer->setVisible(true);

            ui->SendOTP->setVisible(false);
            ui->line_CIN->setVisible(false);
            ui->line_Email->setVisible(false);
            ui->label1->setVisible(false);
            ui->label1_2->setVisible(false);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("CIN Introuvable"), QObject::tr("Le CIN est incorrect"), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur de requête"), QObject::tr("Erreur lors de l'exécution de la requête SQL"), QMessageBox::Cancel);
    }
}



void Resetpass::on_Confirmer_clicked()
{
    QSqlQuery query;
    QString otp = ui->line_OTP->text();
    if(otp == currentOtp){
        query.prepare("UPDATE EMPLOYE SET PASSWORD=:PASSWORD WHERE CIN=:CIN");
        query.bindValue(":PASSWORD", ui->line_Pass->text());
        query.bindValue(":CIN", CIN);
        query.exec();
        close();
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Code incorrect"), QObject::tr("Le code OTP est incorrect"), QMessageBox::Cancel);
    }
}
