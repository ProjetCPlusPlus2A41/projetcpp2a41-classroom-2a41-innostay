    #include "reservation.h"
    #include <QSqlQuery>
    #include <QSqlError>
    #include <QDebug>

    Reservation::Reservation()
    : id(0), etat(""), dateD(QDate()), dateF(QDate()), prix(0), idClient(0) {}


    Reservation::Reservation(int id, const QString& etat, const QDate& dateD, const QDate& dateF, int prix, int idClient)
    : id(id), etat(etat), dateD(dateD), dateF(dateF), prix(prix), idClient(idClient) {}

    int Reservation::getId() const {
        return id;
    }


    bool Reservation::ajouter() {
        QSqlQuery query;

        query.prepare("INSERT INTO RESERVATION (ID, ETAT, DATE_D, DATE_F, PRIX, ID_CLIENT) "
                      "VALUES (:id, :etat, :dateD, :dateF, :prix, :idClient)");

        query.bindValue(":id", id);
        query.bindValue(":etat", etat);
        query.bindValue(":dateD", dateD);
        query.bindValue(":dateF", dateF);
        query.bindValue(":prix", prix);
        query.bindValue(":idClient", idClient);

        if (query.exec()) {
            return true;
        } else {
            qDebug() << "Erreur lors de l'ajout de la réservation :" << query.lastError().text();
            return false;
        }
    }

    bool Reservation::supprimer(int id) {
        QSqlQuery query;
        query.prepare("DELETE FROM RESERVATION WHERE ID = :id");
        query.bindValue(":id", id);
        return query.exec();
    }

    QSqlTableModel* Reservation::afficher() {
        QSqlDatabase db = QSqlDatabase::database(); // Récupère la connexion à la base de données

        if (!db.isOpen()) {
            qDebug() << "La base de données n'est pas ouverte.";
            return nullptr;
        }

        // Création du modèle pour afficher les données
        QSqlTableModel *model = new QSqlTableModel(nullptr, db);
        model->setTable("RESERVATION");

        if (!model->select()) {
            qDebug() << "Erreur lors de la sélection des données :" << model->lastError().text();
            delete model;
            return nullptr;
        }

        return model;
    }


    bool Reservation::modifier(int id, const QString& etat, const QDate& dateD, const QDate& dateF, int prix, int idClient) {
        QSqlQuery query;

        // Préparez la requête SQL pour mettre à jour la réservation
        query.prepare("UPDATE RESERVATION SET ETAT = :etat, DATE_D = :dateD, DATE_F = :dateF, PRIX = :prix, ID_CLIENT = :idClient WHERE ID = :id");

        // Liez les valeurs aux paramètres de la requête
        query.bindValue(":id", id);               // Utiliser l'id passé en paramètre
        query.bindValue(":etat", etat);           // Utiliser l'état passé en paramètre
        query.bindValue(":dateD", dateD);         // Utiliser la date de début passée en paramètre
        query.bindValue(":dateF", dateF);         // Utiliser la date de fin passée en paramètre
        query.bindValue(":prix", prix);           // Utiliser le prix passé en paramètre
        query.bindValue(":idClient", idClient);   // Utiliser l'idClient passé en paramètre

        // Exécutez la requête et gérez le résultat
        if (query.exec()) {
            return true;  // Mise à jour réussie
        } else {
            qDebug() << "Erreur lors de la mise à jour de la réservation :" << query.lastError().text();
            return false;  // Échec de la mise à jour
        }
    }



