#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QSqlQueryModel>
#include<QString>
#include<QTableView>
class employe
{
public:
    employe();
   employe (int,QString,QString);
    int getid();


    QString getnom();
    QString getprenom();
    void setid(int);


    void setnom(QString);
    void setprenom(QString);
bool ajouter();
QSqlQueryModel *afficher();
QSqlQueryModel * tri_prenom();
QSqlQueryModel *tri_nom();
QSqlQueryModel * tri_id();
bool supprimer(int);
 QSqlQueryModel* rechercher(int id);
 void exportt();
void clearTable(QTableView *table);
bool modifier();
QMap<QString, QVariant>getStatistics();
private:
    int ID;
    QString NOM,PRENOM;
};
#endif // EMPLOYE_H
