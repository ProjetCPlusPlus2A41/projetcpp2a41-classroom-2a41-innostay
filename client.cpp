#include "client.h"
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QUrlQuery>
Client::Client()
{
    CIN = 0;
    NUMTEL = 0;
    NOM = "";
    PRENOM = "";
    EMAIL = "";
}
Client::Client(int CIN,QString NOM,QString PRENOM,QString EMAIL,int NUMTEL)
{
    this->CIN = CIN;
    this->NOM = NOM;
    this->PRENOM = PRENOM;
    this->EMAIL = EMAIL;
    this->NUMTEL = NUMTEL;
}
bool Client::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (CIN, NOM, PRENOM, EMAIL, NUMTEL) VALUES (:CIN, :NOM, :PRENOM, :EMAIL, :NUMTEL)");
    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":NUMTEL", NUMTEL);
    return query.exec();
}

bool Client::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET NOM=:NOM, PRENOM=:PRENOM, EMAIL=:EMAIL, NUMTEL=:NUMTEL WHERE CIN=:CIN");
    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":NUMTEL", NUMTEL);
    return query.exec();
}
bool Client::supprimer(int CIN)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENT WHERE CIN = :CIN");
    query.bindValue(":CIN", CIN);
    return query.exec();
}
QSqlQueryModel* Client::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT TO_CHAR(CIN) AS CIN, NOM, PRENOM, EMAIL, TO_CHAR(NUMTEL) AS NUMTEL FROM CLIENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUMTEL"));
    return model;
}
QSqlQueryModel* Client::afficher_cin()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CIN FROM CLIENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    return model;
}
QSqlQueryModel* Client::tri_CIN()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT TO_CHAR(CIN) AS CIN, NOM, PRENOM, EMAIL, TO_CHAR(NUMTEL) AS NUMTEL FROM CLIENT ORDER BY CIN");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUMTEL"));
    return model;
}
QSqlQueryModel* Client::tri_Nom()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT TO_CHAR(CIN) AS CIN, NOM, PRENOM, EMAIL, TO_CHAR(NUMTEL) AS NUMTEL FROM CLIENT ORDER BY NOM");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUMTEL"));
    return model;
}
void Client::clearTable(QTableView *table){
    QSqlQueryModel* modelFeragh= new QSqlQueryModel();
    modelFeragh->clear();
    table->setModel(modelFeragh);
}
void Client::postrequest(QString smsmsg, QString phonenumber) {
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // Replace with your Twilio credentials and phone number
    QString accountSid = "XXXXXXXX";
    QString authToken = "XXXXXXXXX";
    QString fromNumber = "+12523620019"; // Your Twilio phone number

    QUrl url(QString("https://api.twilio.com/2010-04-01/Accounts/%1/Messages.json").arg(accountSid));
    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Set up Basic Auth header
    QString auth = "Basic " + QString("%1:%2").arg(accountSid, authToken).toUtf8().toBase64();
    req.setRawHeader("Authorization", auth.toUtf8());

    // Form the data as application/x-www-form-urlencoded
    QUrlQuery params;
    params.addQueryItem("To", "+216" + phonenumber);
    params.addQueryItem("From", fromNumber);
    params.addQueryItem("Body", smsmsg);

    QByteArray data = params.query().toUtf8();
    QNetworkReply *reply = mgr.post(req, data);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Success" << reply->readAll();
        delete reply;
    } else {
        qDebug() << "Failure" << reply->errorString() << reply->error();
        delete reply;
    }
}

void Client::rechercher(QTableView *table,QString rech)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("SELECT TO_CHAR(CIN) AS CIN, NOM, PRENOM, EMAIL, TO_CHAR(NUMTEL) AS NUMTEL FROM CLIENT WHERE regexp_like(CIN,:X) OR regexp_like(NOM,:X) OR regexp_like(PRENOM,:X);");
    query->bindValue(":X",rech);
    if(rech.isEmpty())
    {
        query->prepare("SELECT TO_CHAR(CIN) AS CIN, NOM, PRENOM, EMAIL, TO_CHAR(NUMTEL) AS NUMTEL FROM CLIENT");
    }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();
}
