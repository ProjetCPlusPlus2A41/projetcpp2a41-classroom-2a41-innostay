#include "connection.h"
#include "qsqlerror.h"
#include <QDebug>

Connection::Connection()
{

}

bool Connection::createConnection()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("smarthotel");//inserer le nom de la source de données
db.setUserName("yessmine");//inserer nom de l'utilisateur
db.setPassword("smarthotel2A41");//inserer mot de passe de cet utilisateur
qDebug() << "Username :" << db.userName();
qDebug() << "password :" << db.password();
if (db.open()){

    test=true;
} else {
    qDebug() << "last error" << db.lastError();
}
return  test;
}
