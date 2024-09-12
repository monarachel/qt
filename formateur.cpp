#include "formateur.h"

#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QTableView>
#include<QSqlQueryModel>
#include<QMessageBox>
#include<QSqlError>

formateur::formateur()
{
    CIN=0;
      NOMFORMATION=" ";             //constructors


}
formateur::formateur (int CIN)
{
    this->CIN=CIN;
}
formateur::formateur (int CIN,QString NOMFORMATION)
{
    this->CIN=CIN;
    this->NOMFORMATION=NOMFORMATION;


}
int formateur::getcin()
{
    return CIN;
}
QString formateur::getnomformation()
{
    return NOMFORMATION ;
}



void formateur::setcin(int CIN)
{
    this->CIN=CIN;

}
void formateur::setnomformation(QString NOMFORMATION)
{
    this->NOMFORMATION=NOMFORMATION;

}



bool formateur::ajouter()
{


    QSqlQuery query;
    QString id_string=QString::number(CIN);



         query.prepare("INSERT INTO FORMATEUR(CIN,NOMFORMATION)" "VALUES (:CIN,:NOMFORMATION)");
         query.bindValue(":CIN", CIN);
         query.bindValue(":NOMFORMATION", NOMFORMATION);

               return query.exec();

}


bool formateur::supprimer(int CIN)
{
    QSqlQuery query;

         query.prepare("DELETE FROM FORMATEUR where CIN= :CIN");
         query.bindValue(0, CIN);

return query.exec();

}


QSqlQueryModel *formateur::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();

          model->setQuery("SELECT* FROM FORMATEUR");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));

          return  model;
}
bool formateur::modifier()
{
    QSqlQuery q;
    // Prepare the SQL update query with named placeholders
    q.prepare("UPDATE FORMATEUR SET NOMFORMATION = :NOMFORMATION WHERE CIN = :CIN");

    // Bind the values to the named placeholders
    q.bindValue(":NOMFORMATION", NOMFORMATION);
    q.bindValue(":CIN", CIN);

    // Execute the query and return the result
    return q.exec();
}


QSqlQueryModel * formateur::tri_cin()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from FORMATEUR order by CIN");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));


    return model;
}


QSqlQueryModel * formateur::tri_nomformation()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from FORMATEUR order by NOMFORMATION");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));

    return model;
}

QSqlQueryModel* formateur::chercheCIN(int CIN)
{
    QSqlQuery query;

    // Préparer la requête pour récupérer NOM
    query.prepare("SELECT NOMFORMATION FROM FORMATEUR WHERE CIN = :CIN");
    query.bindValue(":CIN", CIN);

    QSqlQueryModel* model = new QSqlQueryModel();

    // Exécuter la requête
    if (query.exec()) {
        // Associer le résultat au modèle si la requête réussit
        model->setQuery(query);
    } else {
        // Afficher un message d'erreur si la requête échoue
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur", "Échec de la requête : " + query.lastError().text());
    }

    return model;
}

bool formateur::existe() const {
    // Implémentation pour vérifier si la formation existe
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM FORMATEUR WHERE CIN = :CIN");
    query.bindValue(":CIN", CIN);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

void formateur::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}
