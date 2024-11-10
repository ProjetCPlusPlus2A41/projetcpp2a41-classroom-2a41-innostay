#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>

class EMPLOYE
{
    QString NOM,PRENOM,VILLE,PASSWORD,GESTION;
    int CIN,NUM_TEL,SALAIRE;
    QDate DATE_NAISSANCE,DATE_EMBAUCHE;
public:
    EMPLOYE();
    EMPLOYE(int,QString,QString,QDate,QString,QString,QDate,float,int,QString);

    int getCIN_EMPLOYE() {  return CIN; }
    QString getNOM() { return NOM; }
    QString getPRENOM() { return PRENOM; }
    QDate getDATE_NAISSANCE() {return DATE_NAISSANCE; }
    QString getVILLE() { return VILLE; }
    QString getPASSWORD() { return PASSWORD; }
    QDate getDATE_EMBAUCHE() { return DATE_EMBAUCHE; }
    int getSALAIRE() {  return SALAIRE; }
    int getNUM_TEL() { return NUM_TEL; }
    QString getGESTION() { return GESTION; }


    void setCIN_EMPLOYE(int CIN) { this->CIN = CIN; }
    void setNOM(QString NOM) { this->NOM = NOM; }
    void setPRENOM(QString PRENOM) { this->PRENOM = PRENOM; }
    void setDATE_NAISSANCE(QDate DATE_NAISSANCE) { this->DATE_NAISSANCE = DATE_NAISSANCE; }
    void setVILLE(QString VILLE) { this->VILLE = VILLE; }
    void setPASSWORD(QString PASSWORD) { this->PASSWORD = PASSWORD; }
    void setDATE_EMBAUCHE(QDate DATE_EMBAUCHE) { this->DATE_EMBAUCHE = DATE_EMBAUCHE; }
    void setSALAIRE(int SALAIRE) { this->SALAIRE = SALAIRE; }
    void setNUM_TEL(int NUM_TEL) { this->NUM_TEL = NUM_TEL; }
    void setGESTION(QString GESTION) { this->GESTION = GESTION; }

    /******************************************************************/

       bool ajouter();
       QSqlQueryModel* afficher();
       bool supprimer(int CIN);
       bool modifier();
       QSqlQueryModel* afficher_cin();
       QSqlQueryModel* tri_CIN();
       QSqlQueryModel* tri_Nom();
       QSqlQueryModel* tri_Gestion();
       void clearTable (QTableView* table);
       void rechercher(QTableView *table,QString x);


};

#endif // EMPLOYE_H
