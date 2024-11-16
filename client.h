#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>

class Client
{
    int CIN,NUMTEL;
    QString NOM,PRENOM,EMAIL;
public:
    Client();
    Client(int,QString,QString,QString,int);

    int getCIN() { return CIN; }
    int getNUMTEL() { return NUMTEL; }
    QString getNOM() { return NOM; }
    QString getPRENOM() { return PRENOM; }
    QString getEmail() { return EMAIL; }

    void setCIN(int CIN) { this->CIN = CIN; }
    void setNUMTEL(int NUMTEL) { this->NUMTEL = NUMTEL; }
    void setNOM(QString NOM) { this->NOM = NOM; }
    void setPRENOM(QString PRENOM) { this->PRENOM = PRENOM; }
    void setEmail(QString EMAIL) { this->EMAIL = EMAIL; }

    bool ajouter();
    bool supprimer(int CIN);
    bool modifier();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_cin();
    QSqlQueryModel* tri_CIN();
    QSqlQueryModel* tri_Nom();
    void postrequest(QString smsmsg,QString phonenumber);
    void clearTable (QTableView* table);
    void rechercher(QTableView *table,QString x);






};

#endif // CLIENT_H
