#include "connection.h"
#include <QSqlError>
#include <QDebug>

Connection::Connection() {

    db = QSqlDatabase::addDatabase("QODBC"); // Initialize the database connection only once
    db.setDatabaseName("smarthotel");//smarthotel
    db.setUserName("eya");//eya
    db.setPassword("smarthotel2A41");//smarthotel2A41
}

bool Connection::CreateConnexion() {
    bool test = false;
    if (db.open()) {
        test = true;
    } else {
        qDebug() << "Database Error: " << db.lastError().text();
    }
    return test;
}

void Connection::FermerConnexion() {
    if (db.isOpen()) {
        db.close();
    }
}

bool Connection::OuvrirConnexion() {
    return db.open();
}
