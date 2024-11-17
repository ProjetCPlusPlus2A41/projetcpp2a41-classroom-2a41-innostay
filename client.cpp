#include "client.h"
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QUrlQuery>
#include <QStandardItemModel>
Client::Client()
{
    CIN = 0;
    NUMTEL = 0;
    NOM = "";
    PRENOM = "";
    EMAIL = "";
    PTS_FIDEL = 0;
}
Client::Client(int CIN,QString NOM,QString PRENOM,QString EMAIL,int NUMTEL,int PTS_FIDEL)
{
    this->CIN = CIN;
    this->NOM = NOM;
    this->PRENOM = PRENOM;
    this->EMAIL = EMAIL;
    this->NUMTEL = NUMTEL;
    this->PTS_FIDEL = PTS_FIDEL;

}
bool Client::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (CIN, NOM, PRENOM, EMAIL, NUMTEL, PTS_FIDEL) VALUES (:CIN, :NOM, :PRENOM, :EMAIL, :NUMTEL, :PTS_FIDEL)");
    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":NUMTEL", NUMTEL);
    query.bindValue(":PTS_FIDEL", PTS_FIDEL);
    return query.exec();
}

bool Client::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET NOM=:NOM, PRENOM=:PRENOM, EMAIL=:EMAIL, NUMTEL=:NUMTEL, PTS_FIDEL=:PTS_FIDEL WHERE CIN=:CIN");
    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":NUMTEL", NUMTEL);
    query.bindValue(":PTS_FIDEL", PTS_FIDEL);
    return query.exec();
}
bool Client::supprimer(int CIN)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENT WHERE CIN = :CIN");
    query.bindValue(":CIN", CIN);
    return query.exec();
}


QStandardItemModel* Client::afficher()
{
    QStandardItemModel* model = new QStandardItemModel();

    // Set column headers
    model->setHorizontalHeaderLabels({"CIN", "NOM", "PRENOM", "EMAIL", "NUMTEL", "PTS_FIDEL"});

    QSqlQuery query;
    query.prepare("SELECT CIN, NOM, PRENOM, EMAIL, NUMTEL, PTS_FIDEL FROM CLIENT");
    if (query.exec()) {
        int row = 0;
        while (query.next()) {
            // Create items for each column
            QStandardItem* cinItem = new QStandardItem(query.value(0).toString());
            QStandardItem* nomItem = new QStandardItem(query.value(1).toString());
            QStandardItem* prenomItem = new QStandardItem(query.value(2).toString());
            QStandardItem* emailItem = new QStandardItem(query.value(3).toString());
            QStandardItem* numtelItem = new QStandardItem(query.value(4).toString());
            QStandardItem* ptsFidelItem = new QStandardItem(query.value(5).toString());

            // Get PTS_FIDEL value for coloring logic
            int ptsFidel = query.value(5).toInt();

            // Apply coloring only for PTS_FIDEL >= 20
            if (ptsFidel >= 20) {
                QColor backgroundColor;

                if (ptsFidel >= 20 && ptsFidel <= 39) {
                    backgroundColor = QColor(209, 135, 63); // Bronze
                } else if (ptsFidel >= 40 && ptsFidel <= 69) {
                    backgroundColor = QColor(128, 128, 128); // Silver
                } else if (ptsFidel >= 70) {
                    backgroundColor = QColor(219, 173, 22); // Gold
                }

                // Apply background color to all columns in the row
                cinItem->setBackground(backgroundColor);
                nomItem->setBackground(backgroundColor);
                prenomItem->setBackground(backgroundColor);
                emailItem->setBackground(backgroundColor);
                numtelItem->setBackground(backgroundColor);
                ptsFidelItem->setBackground(backgroundColor);
            }

            // Add items to the model
            model->setItem(row, 0, cinItem);
            model->setItem(row, 1, nomItem);
            model->setItem(row, 2, prenomItem);
            model->setItem(row, 3, emailItem);
            model->setItem(row, 4, numtelItem);
            model->setItem(row, 5, ptsFidelItem);

            row++;
        }
    }

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
    model->setQuery("SELECT TO_CHAR(CIN) AS CIN, NOM, PRENOM, EMAIL, TO_CHAR(NUMTEL) AS NUMTEL, TO_CHAR(PTS_FIDEL) AS PTS_FIDEL FROM CLIENT ORDER BY CIN");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUMTEL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PTS_FIDEL"));
    return model;
}
QSqlQueryModel* Client::tri_Nom()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT TO_CHAR(CIN) AS CIN, NOM, PRENOM, EMAIL, TO_CHAR(NUMTEL) AS NUMTEL, TO_CHAR(PTS_FIDEL) AS PTS_FIDEL FROM CLIENT ORDER BY NOM");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUMTEL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PTS_FIDEL"));
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
    query->prepare("SELECT TO_CHAR(CIN) AS CIN, NOM, PRENOM, EMAIL, TO_CHAR(NUMTEL) AS NUMTEL, TO_CHAR(PTS_FIDEL) AS PTS_FIDEL FROM CLIENT WHERE regexp_like(CIN,:X) OR regexp_like(NOM,:X) OR regexp_like(PRENOM,:X);");
    query->bindValue(":X",rech);
    if(rech.isEmpty())
    {
        query->prepare("SELECT TO_CHAR(CIN) AS CIN, NOM, PRENOM, EMAIL, TO_CHAR(NUMTEL) AS NUMTEL, TO_CHAR(PTS_FIDEL) AS PTS_FIDEL FROM CLIENT");
    }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();
}
