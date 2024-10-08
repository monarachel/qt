#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QSqlQueryModel>
#include<QString>
#include<QTableView>

class employe // declaration des fcts
{
public:
   employe(); //constructeur
   employe (int,QString,QString);
   employe(int);
//getter
    int getid();
    QString getnom();
    QString getprenom();
//setter
    void setid(int);
    void setnom(QString);
    void setprenom(QString);
//les fonctualites
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
bool existe() const;
QMap<QString, QVariant>getStatistics();
private:
    int ID;
    QString NOM,PRENOM;
};
#endif // EMPLOYE_H
