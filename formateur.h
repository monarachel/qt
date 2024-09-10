#ifndef FORMATEUR_H
#define FORMATEUR_H

#include<QSqlQueryModel>
#include<QString>
#include<QTableView>
class formateur
{
public:
    formateur();
   formateur(int,QString);
    int getcin();


    QString getnomformation();

    void setcin(int);


    void setnomformation(QString);

bool ajouter();
QSqlQueryModel *afficher();
QSqlQueryModel * tri_cin();
QSqlQueryModel *tri_nomformation();

bool supprimer(int);
QSqlQueryModel*  chercheCIN(int CIN);
void clearTable(QTableView *table);
bool modifier();
private:
    int CIN;
    QString NOMFORMATION;


};
#endif // FORMATEUR_H
