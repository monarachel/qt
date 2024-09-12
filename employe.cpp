#include "employe.h"

#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<qsqlerror.h>
#include<QTableView>
#include"qprinter.h"
#include<QFileDialog>
#include<QMessageBox>
#include<QSqlError>
#include<qpainter.h>
//code source: l'implémentation des fonctions et des méthodes définies
employe::employe()
{
    ID=0;
      NOM=" ";              //les constructeurs
      PRENOM=" ";

}
employe::employe(int ID)
{
    this->ID=ID;
}
employe::employe (int ID,QString NOM,QString PRENOM)
{
    this->ID=ID;
    this->NOM=NOM;
    this->PRENOM=PRENOM;


}
int employe::getid()
{
    return ID;
}
QString employe::getnom()
{
    return NOM;
}
QString employe::getprenom()
{
    return PRENOM;
}


void employe::setid(int ID)
{
    this->ID=ID;

}
void employe::setnom(QString NOM)
{
    this->NOM=NOM;

}
void employe::setprenom(QString PRENOM)
{
    this->PRENOM=PRENOM;

}


bool employe::ajouter() //implementation de la methode ajouter
{

    QSqlQuery query;
    QString id_string=QString::number(ID);

         query.prepare("INSERT INTO EMPLOYE(ID,NOM,PRENOM)" "VALUES (:ID,:NOM,:PRENOM)");
        //creation des variables liées
         query.bindValue(":ID", ID);
         query.bindValue(":NOM", NOM);
         query.bindValue(":PRENOM", PRENOM);

               return query.exec(); //envoie la requette pour exécution
}


bool employe::supprimer(int ID)
{
    QSqlQuery query;

         query.prepare("DELETE FROM EMPLOYE where ID= :ID");
         query.bindValue(0, ID);

return query.exec();

}


QSqlQueryModel *employe::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();

          model->setQuery("SELECT* FROM EMPLOYE");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));




          return  model;
}

bool employe::modifier()
{
    QSqlQuery q;
    q.prepare("UPDATE EMPLOYE SET ID = :ID, NOM = :NOM, PRENOM = :PRENOM  WHERE ID = :ID");
    q.bindValue(":NOM",NOM );
    q.bindValue(":PRENOM", PRENOM);
    q.bindValue(":ID", ID);

    return q.exec();
}

QSqlQueryModel * employe::tri_id()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from EMPLOYE order by ID");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));


    return model;
}


QSqlQueryModel * employe::tri_nom()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from EMPLOYE order by NOM");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));


    return model;
}



QSqlQueryModel* employe::rechercher(int id)
{
    QSqlQuery query;

    // Préparer la requête pour récupérer NOM et PRENOM
    query.prepare("SELECT NOM, PRENOM FROM EMPLOYE WHERE ID = :ID");
    query.bindValue(":ID", id);

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


void employe::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}


void employe::exportt()
{
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");

            if (filePath.isEmpty()) {
                return;
}
                   QPrinter printer;
                   printer.setOutputFormat(QPrinter::PdfFormat);
                   printer.setOutputFileName(filePath);

                   QPainter painter(&printer);

                   // Commencer le dessin sur la page
                   painter.begin(&printer);

                   // Définir la taille de la page
                   printer.setPageSize(QPrinter::A4);

                   // Définir la police et la taille du texte
                   painter.setFont(QFont("Arial", 12));


                   painter.drawText(100, 100, "Liste des employe");
                   painter.drawText(100, 120, "ID");
                   painter.drawText(200, 120, "NOM");
                   painter.drawText(300, 120, "PRENOM");

                   QSqlQuery query;
                   query.prepare("SELECT * FROM EMPLOYE");
                   if (query.exec()) {
                       int row = 140;
                       int rowCount = 0;
                       while (query.next()) {
                            QString id = query.value("ID").toString();
                           QString NOM = query.value("NOM").toString();
                           QString PRENOM = query.value("PRENOM").toString();


                           painter.drawText(100, row, id);
                           painter.drawText(200, row, NOM);
                           painter.drawText(300, row, PRENOM);
                           row += 20;
                           rowCount++;
                           if (rowCount % 20 == 0) {
                               printer.newPage();
                               row = 100;
                           }
                       }
                   } else {


                   }
                   painter.end();

}

QMap<QString, QVariant> employe::getStatistics()
{
    QMap<QString, QVariant> statistics;

    QSqlQuery query;


    query.exec("SELECT COUNT(*) FROM EMPLOYE");
    if (query.next()) {
        statistics["Total employes: "] = query.value(0);


    query.exec("SELECT SUM(BUDGET) FROM  EMPLOYE");
    if (query.next()) {
        statistics[""] = query.value(0);
    }

    return statistics;
    }}

bool employe::existe() const {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE ID = :id");
    query.bindValue(":id", ID);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}





























QSqlQueryModel * employe::tri_prenom()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from EMPLOYE order by PRENOM");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));


    return model;
}
