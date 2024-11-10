#include "plat.h"

#include <QSqlQuery>

#include <QDebug>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QMessageBox>
#include <QDesktopServices>


// Constructeur par défaut
Plat::Plat() : id_restaurant(0), nom_plat(""), type(""), prix(0), disponibilite("") {}

// Constructeur paramétré
Plat::Plat(int id, QString nom, QString type, double prix, QString disponibilite)
    : id_restaurant(id), nom_plat(nom), type(type), prix(prix), disponibilite(disponibilite) {}

// Getters
int Plat::getId() const { return id_restaurant; }
QString Plat::getNom() const { return nom_plat; }
QString Plat::getType() const { return type; }
double Plat::getPrix() const { return prix; }
QString Plat::getDisponibilite() const { return disponibilite; }

// Ajouter un plat
bool Plat::ajouter() {
    QSqlQuery query;  // Instanciation de QSqlQuery
    query.prepare("INSERT INTO plats (id_restaurant,nom_plat,type,disponibilite,prix ) VALUES (:id_restaurant,:nom,:type,:disponibilite,:prix)");
    query.bindValue(":id_restaurant", id_restaurant);
    query.bindValue(":nom", nom_plat);
    query.bindValue(":type", type);
    query.bindValue(":prix", prix);
    query.bindValue(":disponibilite", disponibilite);

    if (query.exec()) {
        qDebug() << "Plat ajouté avec succès!";
        return true;
    } else {
        qDebug() << "Erreur lors de l'ajout du plat:" << query.lastError();
        return false;
    }
}
//afficher
QSqlQueryModel* Plat::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from plats");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_restaurant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_plat"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("disponibilite"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
   return model;

}

// Modifier un plat
bool Plat::modifier() {
    QSqlQuery query;  // Instanciation de QSqlQuery
    query.prepare("UPDATE plats SET nom_plat = :nom, type = :type, prix = :prix, disponibilite = :disponibilite WHERE id_restaurant = :id");
    query.bindValue(":id", id_restaurant);
    query.bindValue(":nom", nom_plat);
    query.bindValue(":type", type);
    query.bindValue(":prix", prix);
    query.bindValue(":disponibilite", disponibilite);

    if (query.exec()) {
        qDebug() << "Plat modifié avec succès!";
        return true;
    } else {
        qDebug() << "Erreur lors de la modification du plat:" << query.lastError();
        return false;
    }
}

//supprimer un plat
bool Plat::supprimer(int id) {
    QSqlQuery query;  // Instanciation de QSqlQuery
    query.prepare("DELETE FROM plats WHERE id_restaurant = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        qDebug() << "Plat supprimé avec succès!";
        return true;
    } else {
        qDebug() << "Erreur lors de la suppression du plat:" << query.lastError();
        return false;
    }
}
//tri
QSqlQueryModel* Plat::tri()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from plats ORDER BY PRIX ASC");//DESC ou ASC
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_restaurant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_plat"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("disponibilite"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
   return model;

}
/*
// Recherche par prix
QList<Plat> Plat::rechercherParPrix(double prixMin, double prixMax) {
    QList<Plat> platsTrouves; // Liste pour stocker les plats trouvés
    QSqlQuery query; // Instanciation de QSqlQuery
    query.prepare("SELECT * FROM plats WHERE prix BETWEEN :prixMin AND :prixMax");
    query.bindValue(":prixMin", prixMin);
    query.bindValue(":prixMax", prixMax);

    if (query.exec()) {
        while (query.next()) {
            // Récupération des données pour chaque plat trouvé
            int id = query.value("id").toInt();
            QString nom = query.value("nom").toString();
            QString type = query.value("type").toString();
            double prix = query.value("prix").toDouble();
            QString disponibilite = query.value("disponibilite").toString();

            // Création d'un objet Plat et ajout à la liste
            Plat plat(id, nom, type, prix, disponibilite);
            platsTrouves.append(plat);
        }
    } else {
        qDebug() << "Erreur lors de la recherche des plats:" << query.lastError();
    }

    return platsTrouves; // Retourne la liste des plats trouvés
}
//statistique de vente
double Plat::calculerTotalVentes() {
    QSqlQuery query;
    query.prepare("SELECT SUM(prix) FROM ventes");  // La table 'ventes' doit exister avec un champ 'prix'

    if (!query.exec()) {
        qDebug() << "Erreur lors du calcul du total des ventes:" << query.lastError();
        return 0.0;
    }

    double totalVentes = 0.0;
    if (query.next()) {
        totalVentes = query.value(0).toDouble();  // Récupère la somme des prix
    }

    qDebug() << "Total des ventes calculé:" << totalVentes;
    return totalVentes;
}


QMap<QString, int> Plat::statistiquesVentes() {
    QMap<QString, int> stats;  // Création d'un QMap pour stocker les statistiques des ventes
    QSqlQuery query;

    // Requête SQL pour obtenir le nombre de ventes par type de plat
    query.prepare("SELECT type, COUNT(*) AS nombre_ventes FROM plats GROUP BY type");

    if (query.exec()) {
        while (query.next()) {
            QString type = query.value("type").toString();  // Récupère le type de plat
            int nombreVentes = query.value("nombre_ventes").toInt();  // Récupère le nombre de ventes
            stats.insert(type, nombreVentes);  // Insère le type de plat et le nombre de ventes dans la map
        }
        qDebug() << "Statistiques de ventes obtenues avec succès!";
    } else {
        qDebug() << "Erreur lors de l'obtention des statistiques de ventes:" << query.lastError();
    }

    return stats;  // Retourne la map contenant les statistiques
}

QList<Plat> Plat::getPlatsParRestaurant(int idRestaurant) {
    QList<Plat> plats;
    QSqlQuery query;
    query.prepare("SELECT * FROM plats WHERE id_restaurant = :id_restaurant");
    query.bindValue(":id_restaurant", idRestaurant);

    if (query.exec()) {
        while (query.next()) {
            int id = query.value("id").toInt();
            QString nom = query.value("nom").toString();
            QString type = query.value("type").toString();
            double prix = query.value("prix").toDouble();
            QString disponibilite = query.value("disponibilite").toString();

            Plat plat(id, nom, type, prix, disponibilite);
            plats.append(plat);
        }
    } else {
        qDebug() << "Erreur lors de la récupération des plats : " << query.lastError();
    }

    return plats;
}
*/
void Plat::exporterEnPDF() {
    QPdfWriter pdf("C:/Users/lenovo/OneDrive - ESPRIT/Bureau/interfaceeya/plat.pdf");

           QPainter painter(&pdf);
           int i = 4100;
          const QImage image("C:/Users/lenovo/OneDrive - ESPRIT/Bureau/innostay__5_-removebg-preview3.png");
                       const QPoint imageCoordinates(155,0);
                       int width1 = 2000;
                       int height1 = 2000;
                       QImage img=image.scaled(width1,height1);
                       painter.drawImage(imageCoordinates, img );

                  QColor dateColor(0x4a5bcf);
                  painter.setPen(dateColor);

                  painter.setFont(QFont("Montserrat SemiBold", 11));
                  QDate cd = QDate::currentDate();
                  painter.drawText(7700,250,cd.toString("Ariana, El Ghazela"));
                  painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

                  QColor titleColor(0x341763);
                  painter.setPen(titleColor);
                  painter.setFont(QFont("Montserrat SemiBold", 25));

                  painter.drawText(3000,2700,"Liste des plats");

                  painter.setPen(Qt::black);
                  painter.setFont(QFont("Time New Roman", 15));
                  //painter.drawRect(100,100,9400,2500);
                  painter.drawRect(100,3300,9400,500);

                  painter.setFont(QFont("Montserrat SemiBold", 10));
                              painter.drawText(300,3600,"id_restaurant");
                              painter.drawText(2000,3600,"nom_plat");
                              painter.drawText(3000,3600,"type");
                              painter.drawText(4000,3600,"disponibilite");
                              painter.drawText(5000,3600,"prix");

                  painter.setFont(QFont("Montserrat", 10));
                  painter.drawRect(100,3300,9400,9000);

                  QSqlQuery query;
                  query.prepare("select * from PLATS");
                  query.exec();
                  int y=4300;
                  while (query.next())
                  {
                      painter.drawLine(100,y,9490,y);
                      y+=500;
                      painter.drawText(300,i,query.value(0).toString());
                          painter.drawText(2000,i,query.value(1).toString());
                          painter.drawText(3000,i,query.value(2).toString());
                          painter.drawText(4000,i,query.value(3).toString());
                          painter.drawText(5000,i,query.value(4).toString());
                     i = i + 500;
                  }


                      QDesktopServices::openUrl( QUrl::fromLocalFile("C:/Users/lenovo/OneDrive - ESPRIT/Bureau/interfaceeya/plat.pdf"));
                      painter.end();

}

QSqlQueryModel * Plat::rechercher(QString NOM)
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM PLATS WHERE NOM_PLAT like '%"+NOM+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_restaurant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_plat"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("disponibilite"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
    return model;
}

bool Plat::insertImageIntoDatabase(const QByteArray& imageData,int ID) {
       QSqlQuery query;
       query.prepare("UPDATE plats SET image = :imageData WHERE id_restaurant = :id");
       query.bindValue(":imageData", imageData);
       query.bindValue(":id", ID);
       // Execute the query
       if (!query.exec()) {
           qDebug() << "Failed to insert image into database:";
           return false;
       }

       return true;
}
