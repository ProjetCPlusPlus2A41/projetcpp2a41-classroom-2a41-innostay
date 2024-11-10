#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>

class Connection {
public:
    Connection();
    bool createConnect(); // Corrigez le nom ici pour correspondre avec celui du main
private:
    QSqlDatabase db;
};

#endif // CONNECTION_H
