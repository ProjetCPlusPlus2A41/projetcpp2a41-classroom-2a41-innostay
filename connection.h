#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{
private:
    QSqlDatabase db;
public:
    Connection();
    bool createConnection();  // Changez ici pour correspondre au .cpp
    void closeConnection();
};

#endif // CONNECTION_H
