#include "employe.h"
#include<QString>
#include<QDate>
#include<QSqlQuery>
#include <QSqlQueryModel>


EMPLOYE::EMPLOYE()
{
    NOM = "";
    PRENOM = "";
    VILLE = "";
    PASSWORD = "";
    NUM_TEL = 0;
    GESTION = "";
    CIN = 0;
    SALAIRE = 0.0;
    DATE_NAISSANCE = QDate();
    DATE_EMBAUCHE = QDate();
}
EMPLOYE::EMPLOYE(int CIN, QString NOM, QString PRENOM, QDate DATE_NAISSANCE, QString VILLE, QString PASSWORD, QDate DATE_EMBAUCHE, float SALAIRE, int NUM_TEL, QString GESTION)
{
    this->CIN = CIN;
    this->NOM = NOM;
    this->PRENOM = PRENOM;
    this->DATE_NAISSANCE = DATE_NAISSANCE;
    this->VILLE = VILLE;
    this->PASSWORD = PASSWORD;
    this->DATE_EMBAUCHE = DATE_EMBAUCHE;
    this->SALAIRE = SALAIRE;
    this->NUM_TEL = NUM_TEL;
    this->GESTION = GESTION;
}

/***********************************************************************************/

bool EMPLOYE::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE (CIN, NOM, PRENOM, DATE_NAISSANCE, VILLE, PASSWORD, DATE_EMBAUCHE, SALAIRE, NUM_TEL, GESTION)"
                  "VALUES (:CIN, :NOM, :PRENOM, :DATE_NAISSANCE, :VILLE, :PASSWORD, :DATE_EMBAUCHE, :SALAIRE, :NUM_TEL, :GESTION)");
    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":DATE_NAISSANCE", DATE_NAISSANCE);
    query.bindValue(":VILLE", VILLE);
    query.bindValue(":PASSWORD", PASSWORD);
    query.bindValue(":DATE_EMBAUCHE", DATE_EMBAUCHE);
    query.bindValue(":SALAIRE", SALAIRE);
    query.bindValue(":NUM_TEL", NUM_TEL);
    query.bindValue(":GESTION", GESTION);

    return query.exec();
}

QSqlQueryModel* EMPLOYE::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT TO_CHAR(CIN) AS CIN, NOM, PRENOM, TO_CHAR(DATE_NAISSANCE, 'DD/MM/YYYY') AS DATE_NAISSANCE, VILLE, PASSWORD, TO_CHAR(DATE_EMBAUCHE, 'DD/MM/YYYY') AS DATE_EMBAUCHE, SALAIRE, TO_CHAR(NUM_TEL) AS NUM_TEL, GESTION FROM EMPLOYE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("VILLE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PASSWORD"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DATE_EMBAUCHE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("GESTION"));
    return model;
}



bool EMPLOYE::supprimer(int CIN)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYE WHERE CIN = :CIN");
    query.bindValue(":CIN", CIN);

    return query.exec();
}


bool EMPLOYE::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET NOM=:NOM, PRENOM=:PRENOM, DATE_NAISSANCE=:DATE_NAISSANCE, VILLE=:VILLE, PASSWORD=:PASSWORD, DATE_EMBAUCHE=:DATE_EMBAUCHE, SALAIRE=:SALAIRE, NUM_TEL=:NUM_TEL, GESTION=:GESTION WHERE CIN=:CIN");
    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":DATE_NAISSANCE", DATE_NAISSANCE);
    query.bindValue(":VILLE", VILLE);
    query.bindValue(":PASSWORD", PASSWORD);
    query.bindValue(":DATE_EMBAUCHE", DATE_EMBAUCHE);
    query.bindValue(":SALAIRE", SALAIRE);
    query.bindValue(":NUM_TEL", NUM_TEL);
    query.bindValue(":GESTION", GESTION);

    return query.exec();
}


QSqlQueryModel* EMPLOYE::afficher_cin()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CIN FROM EMPLOYE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    return model;
}


QSqlQueryModel* EMPLOYE::tri_CIN()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT TO_CHAR(CIN) AS CIN, NOM, PRENOM, TO_CHAR(DATE_NAISSANCE, 'DD/MM/YYYY') AS DATE_NAISSANCE, VILLE, PASSWORD, TO_CHAR(DATE_EMBAUCHE, 'DD/MM/YYYY') AS DATE_EMBAUCHE, SALAIRE, TO_CHAR(NUM_TEL) AS NUM_TEL, GESTION FROM EMPLOYE ORDER BY CIN");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("VILLE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PASSWORD"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DATE_EMBAUCHE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("GESTION"));
    return model;
}


QSqlQueryModel* EMPLOYE::tri_Nom()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT TO_CHAR(CIN) AS CIN, NOM, PRENOM, TO_CHAR(DATE_NAISSANCE, 'DD/MM/YYYY') AS DATE_NAISSANCE, VILLE, PASSWORD, TO_CHAR(DATE_EMBAUCHE, 'DD/MM/YYYY') AS DATE_EMBAUCHE, SALAIRE, TO_CHAR(NUM_TEL) AS NUM_TEL, GESTION FROM EMPLOYE ORDER BY NOM");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("VILLE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PASSWORD"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DATE_EMBAUCHE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("GESTION"));
    return model;
}

QSqlQueryModel* EMPLOYE::tri_Gestion()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT TO_CHAR(CIN) AS CIN, NOM, PRENOM, TO_CHAR(DATE_NAISSANCE, 'DD/MM/YYYY') AS DATE_NAISSANCE, VILLE, PASSWORD, TO_CHAR(DATE_EMBAUCHE, 'DD/MM/YYYY') AS DATE_EMBAUCHE, SALAIRE, TO_CHAR(NUM_TEL) AS NUM_TEL, GESTION FROM EMPLOYE ORDER BY GESTION");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("VILLE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PASSWORD"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DATE_EMBAUCHE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("GESTION"));
    return model;
}

void EMPLOYE::clearTable(QTableView *table){
    QSqlQueryModel* modelFeragh= new QSqlQueryModel();
    modelFeragh->clear();
    table->setModel(modelFeragh);
}

void EMPLOYE::rechercher(QTableView *table,QString rech)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("SELECT TO_CHAR(CIN) AS CIN, NOM, PRENOM, TO_CHAR(DATE_NAISSANCE, 'DD/MM/YYYY') AS DATE_NAISSANCE, VILLE, PASSWORD, TO_CHAR(DATE_EMBAUCHE, 'DD/MM/YYYY') AS DATE_EMBAUCHE, SALAIRE, TO_CHAR(NUM_TEL) AS NUM_TEL, GESTION FROM EMPLOYE WHERE regexp_like(CIN,:X) OR regexp_like(NOM,:X) OR regexp_like(PRENOM,:X);");
    query->bindValue(":X",rech);
    if(rech.isEmpty())
    {
        query->prepare("SELECT TO_CHAR(CIN) AS CIN, NOM, PRENOM, TO_CHAR(DATE_NAISSANCE, 'DD/MM/YYYY') AS DATE_NAISSANCE, VILLE, PASSWORD, TO_CHAR(DATE_EMBAUCHE, 'DD/MM/YYYY') AS DATE_EMBAUCHE, SALAIRE, TO_CHAR(NUM_TEL) AS NUM_TEL, GESTION FROM EMPLOYE");
    }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();
}





