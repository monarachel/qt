#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"employe.h"
#include<QMessageBox>
#include"formateur.h"
#include<QSqlRecord>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
      ui->letab->setModel(e.afficher());

      ui->letab_2->setModel(c.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajout_clicked() // appel de la methode ajouter
{
    int ID=ui->leid->text().toInt(); //Convertir la chaine saisie en un entier car l’attribut id est de type int
    QString NOM=ui->lenom->text();
    QString PRENOM=ui->leprenom->text();

    employe e (ID,NOM,PRENOM);
    bool test=e.ajouter();
    if(test)
    {    ui->letab->setModel(e.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("ajout effectué\n""click cancel to exit."),QMessageBox::Cancel);
    }else
        QMessageBox::critical(nullptr,QObject::tr("ok"),QObject::tr("ajout non effectué\n""click cancel to exit."),QMessageBox::Cancel);

    // Clear the input fields after adding the employee
        ui->leid->clear();
        ui->lenom->clear();
        ui->leprenom->clear();
}

void MainWindow::on_affiche_clicked()
{
e.afficher();
}

void MainWindow::on_supprime_clicked()
{

    int id=ui->leid1->text().toInt();
    bool test=e.supprimer(id);
    if(test)
    {   ui->letab->setModel(e.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("suppression effectueé\n""click cancel to exit."),QMessageBox::Cancel);
    }else
        QMessageBox::critical(nullptr,QObject::tr("ok"),QObject::tr("supression non effectueé\n""click cancel to exit."),QMessageBox::Cancel);

    // Clear the input field after deletion
        ui->leid1->clear();
}

void MainWindow::on_clear_clicked()

{
    QString idText = ui->leid2->text();
    int id = idText.toInt();  // Convertir l'ID en entier
    QString prenom = ui->leprenom2->text();
    QString nom = ui->lenom2->text();

    // verifier si l'ID est vide
        if (idText.isEmpty()) {
            QMessageBox::critical(nullptr, QObject::tr("Modifier employe"),
                        QObject::tr("Employé non modifié. ID invalide.\n"
                                    "Cliquer quitter."), QMessageBox::Cancel);
            return;
        }

        // si prenom vide
    if (prenom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier employe"),
                    QObject::tr("Employe non Modifié. Prénom invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    // si nom vide
    if (nom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier employe"),
                    QObject::tr("Employe non Modifie. Nom invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }


    employe e (id, nom, prenom);

    if(e.modifier()) {
        QMessageBox::information(nullptr, QObject::tr("Modifier employe"),
                    QObject::tr("Employe modifié.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        ui->letab->setModel(e.afficher());

        // Clear the input fields after modification
                ui->leid2->clear();
                ui->leprenom2->clear();
                ui->lenom2->clear();
    }
  }

void MainWindow::on_letrie_clicked()
{employe e;
       ui->letab->setModel(e.tri_nom());
}

void MainWindow::on_letrie2_clicked()
{
    employe e;
           ui->letab->setModel(e.tri_id());
}

void MainWindow::on_clear_2_clicked(){



int CIN = ui->leid2_2->text().toInt();
QString NOMFORMATION = ui->lenom2_2->text();


if (NOMFORMATION.isEmpty()) {
    QMessageBox::critical(nullptr, QObject::tr("Modifier formateur"),
                QObject::tr("formateur non Modifie. Nom invalide.\n"
                            "Cliquer quitter."), QMessageBox::Cancel);
    return;
}

formateur h (CIN,NOMFORMATION);

if(h.modifier()) {
    QMessageBox::information(nullptr, QObject::tr("Modifier formateur"),
                QObject::tr("modifié.\n"
                            "Cliquer quitter."), QMessageBox::Cancel);
    ui->letab_2->setModel(h.afficher());

    // Clear the input fields after modification
           ui->leid2_2->clear();
           ui->lenom2_2->clear();

}
}

void MainWindow::on_ajout_2_clicked()
{int CIN=ui->leid_2->text().toInt();
    QString NOMFORMATION=ui->lenom_2->text();


    formateur h (CIN,NOMFORMATION);
    bool test=h.ajouter();
    if(test)
    {    ui->letab_2->setModel(h.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("ajouter effectueé\n""click cancel to exit."),QMessageBox::Cancel);
        // Nettoyer les champs de saisie après l'ajout
               ui->leid_2->clear();
               ui->lenom_2->clear();
    }else
        QMessageBox::critical(nullptr,QObject::tr("ok"),QObject::tr("ajouter non effectueé\n""click cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_affiche_2_clicked()
{c.afficher();

}

void MainWindow::on_supprime_2_clicked()
{
    int CIN=ui->leid1_2->text().toInt();
    bool test=c.supprimer(CIN);
    if(test)
    {   ui->letab_2->setModel(c.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("suppression effectueé\n""click cancel to exit."),QMessageBox::Cancel);

        // Clear the input fields after successful deletion
               ui->leid1_2->clear();
    }else
        QMessageBox::critical(nullptr,QObject::tr("ok"),QObject::tr("supression non effectueé\n""click cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_letrie_2_clicked()
{
  formateur h;
           ui->letab_2->setModel(h.tri_nomformation());
}

void MainWindow::on_letrie2_2_clicked()
{
    formateur h;
           ui->letab_2->setModel(h.tri_cin());
}

void MainWindow::on_pushButton_clicked()
{
    employe F1;

    // Récupérer l'ID tapé dans le champ lineEdit_id
    int id = ui->lineEdit_2->text().toInt();

    // Appeler la méthode rechercher avec l'ID pour obtenir un modèle
    QSqlQueryModel* model = F1.rechercher(id);

    QMessageBox msgBox;

    if (model && model->rowCount() > 0) {
        // Extraire les données de la première ligne retournée
        QString nom = model->record(0).value("NOM").toString();
        QString prenom = model->record(0).value("PRENOM").toString();

        // Afficher les coordonnées de l'employé
        QString coordonnees = QString("ID: %1\nNOM: %2\nPRENOM: %3")
            .arg(id)
            .arg(nom)
            .arg(prenom);

        msgBox.setText("Recherche réussie\n\n" + coordonnees);

        // Mettre à jour la table dans l'interface utilisateur avec le modèle
        ui->letab->setModel(model);
    } else {
        // Aucun résultat trouvé
        msgBox.setText("Échec de la recherche : Aucun employé trouvé avec cet ID.");
    }

    // Afficher le message dans un pop-up
    msgBox.exec();

     ui->lineEdit_2->clear();

     // Mettre à jour la table avec tous les employés après la recherche
        ui->letab->setModel(F1.afficher());  // `afficher()` method to get the full list of employees

}


void MainWindow::on_pushButton_2_clicked()
{
    formateur F1;

    // Récupérer l'ID tapé dans le champ lineEdit_id
    int cin = ui->lineEdit_3->text().toInt();

    // Appeler la méthode rechercher avec l'ID pour obtenir un modèle
    QSqlQueryModel* model = F1.chercheCIN(cin);
    QMessageBox msgBox;

    if (model && model->rowCount() > 0) {
        // Extraire les données de la première ligne retournée
        QString nom = model->record(0).value("NOMFORMATION").toString();

        // Afficher les coordonnées formateur
        QString coordonnees = QString("CIN: %1\nNOMFORMATION: %3")
            .arg(cin)
            .arg(nom);

        msgBox.setText("Recherche réussie\n\n" + coordonnees);

        // Mettre à jour la table dans l'interface utilisateur avec le modèle
        ui->letab_2->setModel(model);
    } else {
        // Aucun résultat trouvé
        msgBox.setText("Échec de la recherche : Aucun employé trouvé avec cet CIN.");
    }

    // Afficher le message dans un pop-up
    msgBox.exec();

     ui->lineEdit_3->clear();

     // Mettre à jour la table avec tous les formateurs après la recherche (refresh ,actualiser
         ui->letab_2->setModel(F1.afficher());  // `afficher()` method to get the full list of formateurs

}

void MainWindow::on_exportpdf_clicked()
{
      e.exportt();
}

void MainWindow::on_pushButton_3_clicked()
{
    {
       employe F;

        // Appelez la fonction statistique
        QMap<QString, QVariant> statistics = F.getStatistics();

        // Affichez les résultats où vous le souhaitez, par exemple dans une boîte de dialogue
        QString message = "Statistiques des employes:\n";
        for (auto it = statistics.begin(); it != statistics.end(); ++it) {
            message += QString("%1: %2\n").arg(it.key(), it.value().toString());
        }

        QMessageBox::information(this, "Statistiques", message);

}}
