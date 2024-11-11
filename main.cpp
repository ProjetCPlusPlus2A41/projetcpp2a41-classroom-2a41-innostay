// main.cpp
#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "reservation.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;
    Reservation reservationTemp;  // Créez un objet de la classe Service pour gérer les données des services

    bool test = c.createconnect();  // Connexion à la base de données
    if (test)
    {
        w.show();

        // Rafraîchir l'affichage du QTableView via la méthode publique
        QSqlQueryModel *model = reservationTemp.afficher();  // Obtenez les données de la base de données
        w.setTableModel(model);  // Utilisez la méthode publique pour associer le modèle au QTableView

        // Affichage d'un message de succès pour la connexion
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("Connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        // Si la connexion échoue, afficher un message d'erreur
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("Connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    return a.exec();
}
