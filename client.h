#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QStandardItemModel>

class Client
{
    int CIN,NUMTEL,PTS_FIDEL;
    QString NOM,PRENOM,EMAIL;
public:
    Client();
    Client(int,QString,QString,QString,int,int);

    int getCIN() { return CIN; }
    int getNUMTEL() { return NUMTEL; }
    QString getNOM() { return NOM; }
    QString getPRENOM() { return PRENOM; }
    QString getEmail() { return EMAIL; }
    int getPTS_FIDEL() { return PTS_FIDEL; }

    void setCIN(int CIN) { this->CIN = CIN; }
    void setNUMTEL(int NUMTEL) { this->NUMTEL = NUMTEL; }
    void setNOM(QString NOM) { this->NOM = NOM; }
    void setPRENOM(QString PRENOM) { this->PRENOM = PRENOM; }
    void setEmail(QString EMAIL) { this->EMAIL = EMAIL; }
    void setPTS_FIDEL(int PTS_FIDEL) { this->PTS_FIDEL = PTS_FIDEL; }

    bool ajouter();
    bool supprimer(int CIN);
    bool modifier();
    QStandardItemModel* afficher();
    QSqlQueryModel* afficher_cin();
    QSqlQueryModel* tri_CIN();
    QSqlQueryModel* tri_Nom();
    void postrequest(QString smsmsg,QString phonenumber);
    void clearTable (QTableView* table);
    void rechercher(QTableView *table,QString x);






};

#endif // CLIENT_H
