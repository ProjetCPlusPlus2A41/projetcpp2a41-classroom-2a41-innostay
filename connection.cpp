#include "connection.h"


Connection::Connection()
{

}

bool Connection::createConnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("smarthotel2A41");//inserer le nom de la source de données
db.setUserName("eya");//inserer nom de l'utilisateur
db.setPassword("eya2A41");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
