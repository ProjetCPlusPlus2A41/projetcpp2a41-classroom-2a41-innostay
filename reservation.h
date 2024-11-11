#ifndef RESERVATION_H
#define RESERVATION_H

#include <QString>
#include <QDate>
#include <QSqlTableModel>

class Reservation {
public:
    Reservation();
    Reservation(int id, const QString& etat, const QDate& dateD, const QDate& dateF, int prix, int idClient);

    bool ajouter();
    bool supprimer(int id);
    QSqlTableModel* afficher();
    bool modifier(int id, const QString& etat, const QDate& dateD, const QDate& dateF, int prix, int idClient);
    int getId() const; // Ajout de la méthode d'accès

private:
    int id;
    QString etat;
    QDate dateD;
    QDate dateF;
    int prix;
    int idClient;
};

#endif // RESERVATION_H
