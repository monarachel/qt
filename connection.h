#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

class Connection // declaration des fcts
{
public:
    Connection();
     bool createconnect(); //etablir la connection
};

#endif // CONNECTION_H
