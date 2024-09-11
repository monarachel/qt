#include "connection.h"
#include <QDebug>
#include <QSqlError>

Connection::Connection()
{

}

bool Connection::createconnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC"); //L’attribut db sera initialisé dans la méthode createconnection() qui établie la connexion à la BD
    db.setDatabaseName("Source_Projet2A"); //nom de la source de donnée QODBC
    db.setUserName("mouna"); // nom user
    db.setPassword("esprit18"); //mot de passe

    if (db.open()) {
        test = true;
    } else {
        qDebug() << "Erreur: " << db.lastError().text();
    }

    return test;
}
