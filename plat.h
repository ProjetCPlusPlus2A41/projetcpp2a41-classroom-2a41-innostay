#ifndef PLAT_H
#define PLAT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QSqlQueryModel>


class Plat {
private:
    int id_restaurant;
    QString nom_plat;
    QString type;
    double prix;
    QString disponibilite;

public:
    Plat();  // Constructeur par défaut
    Plat(int id, QString nom, QString type, double prix, QString disponibilite);  // Constructeur paramétré

    // Getters
    int getId() const;
    QString getNom() const;
    QString getType() const;
    double getPrix() const;
    QString getDisponibilite() const;

    // Méthodes CRUD
    bool ajouter();
    QSqlQueryModel *afficher();
    bool modifier();
    bool supprimer(int id);
     QSqlQueryModel *tri();
     QSqlQueryModel *rechercher(QString NOM);
    static QList<Plat> getPlatsParRestaurant(int idRestaurant);
    void exporterEnPDF();

    bool insertImageIntoDatabase(const QByteArray& imageData,int ID);


};

#endif // PLAT_H
