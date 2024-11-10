#include "client.h"

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
