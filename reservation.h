#ifndef RESERVATION_H
#define RESERVATION_H

#include <QString>
#include <QDate>
#include <QSqlTableModel>
#include <QString>
#include <QImage>

class Reservation {
public:
    Reservation();
    Reservation(int id, const QString& etat, const QDate& dateD, const QDate& dateF, int prix, int idClient);

    bool ajouter();
    bool supprimer(int id);
    QSqlTableModel* afficher();
    bool modifier(int id, const QString& etat, const QDate& dateD, const QDate& dateF, int prix, int idClient);
    int getId() const; // Ajout de la méthode d'accès
    QSqlTableModel* afficher1();
    QSqlTableModel* trierPar(const QString &colonne, Qt::SortOrder ordre);
    QSqlTableModel* rechercherParID(int id);
     QStringList getReservationsForDate(const QDate &date) const;

     QString getReservationDetails() const;







private:
    int id;
    QString etat;
    QDate dateD;
    QDate dateF;
    int prix;
    int idClient;
};

#endif // RESERVATION_H
