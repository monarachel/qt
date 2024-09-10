#include "connection.h"
#include <QDebug>
#include <QSqlError>

Connection::Connection()
{

}

bool Connection::createconnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("mouna");
    db.setPassword("esprit18");

    if (db.open()) {
        test = true;
    } else {
        qDebug() << "Erreur: " << db.lastError().text();
    }

    return test;
}
