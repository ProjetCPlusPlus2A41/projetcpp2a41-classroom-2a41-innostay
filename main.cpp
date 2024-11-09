#include <QApplication>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QApplication>
#include "connection.h"
#include "mainwindow.h"
void connectToDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    if (!QSqlDatabase::isDriverAvailable("QSQLITE")) {
        qDebug() << "Pilote SQLite non disponible !";
        return;
    }

    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/base_de_donnees.db");

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données :" << db.lastError().text();
    } else {
        qDebug() << "Connexion réussie à la base de données !";
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Connexion à la base de données
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");  // Utilisez "QSQLITE" si vous utilisez SQLite
    db.setDatabaseName("instantclient_23_5");  // Remplacez par le nom de votre base de données
    db.setUserName("yessmine");  // Remplacez par votre nom d'utilisateur
    db.setPassword("smarthotel2A41");  // Remplacez par votre mot de passe

    // Vérification de la connexion à la base de données
    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur de connexion"),
            QObject::tr("Impossible de se connecter à la base de données.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        QStringList drivers = QSqlDatabase::drivers();
            qDebug() << "Drivers disponibles :" << drivers;
        return -1;
    }
connectToDatabase();
    // Démarrage de la fenêtre principale
    MainWindow w;
    w.show();

    return a.exec();


    Connection c;
    bool test=c.createConnection();
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}

