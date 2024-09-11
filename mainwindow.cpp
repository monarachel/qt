#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"employe.h"
#include<QMessageBox>
#include"formateur.h"
#include<QSqlRecord>

//la classe responsable de l'interface utilisateur principale de l'application.

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->letab->setModel(new QSqlQueryModel());    // le model va etre vide lors de l'execution
        ui->letab_2->setModel(new QSqlQueryModel());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajout_clicked()
{
    // Récupérer les données saisies par l'utilisateur
    QString idText = ui->leid->text();
    QString nom = ui->lenom->text();
    QString prenom = ui->leprenom->text();

    // Vérifier que tous les champs sont remplis
    if (idText.isEmpty() || nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(this, QObject::tr("Erreur"), QObject::tr("Tous les champs doivent être remplis."));
        return;
    }

    // Convertir l'ID en entier et vérifier que la conversion est réussie
    bool ok;
    int id = idText.toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, QObject::tr("Erreur"), QObject::tr("L'ID doit être un entier positif."));
        return;
    }

    // Créer un objet employe avec les données validées
    employe e(id, nom, prenom);

    // Appeler la méthode ajouter et vérifier si l'ajout a réussi
    bool test = e.ajouter();
    if (test) {
        // Mettre à jour la table dans l'interface utilisateur
        ui->letab->setModel(e.afficher());
        QMessageBox::information(this, QObject::tr("Succès"), QObject::tr("Ajout effectué.\nCliquez sur OK pour quitter."));
    } else {
        QMessageBox::critical(this, QObject::tr("Erreur"), QObject::tr("Ajout non effectué.\nCliquez sur OK pour quitter."));
    }

    // Vider les champs de saisie après l'ajout
    ui->leid->clear();
    ui->lenom->clear();
    ui->leprenom->clear();
}


void MainWindow::on_affiche_clicked()
{

    QSqlQueryModel* model = e.afficher();

    // Mise à jour de la vue de table avec les données récupérées
    ui->letab->setModel(model);
}


void MainWindow::on_supprime_clicked()
{
    int id = ui->leid1->text().toInt(); // Convertir le texte en entier

    employe e(id); // Créer un objet employé avec l'ID fourni

    // Vérifier si l'employé existe avant de tenter la suppression
    if (!e.existe()) {
        QMessageBox::warning(nullptr, QObject::tr("Suppression employé"),
                    QObject::tr("Échec de la suppression : L'employé avec cet ID n'existe pas.\n"
                                "Cliquer OK pour quitter."), QMessageBox::Ok);
        return;
    }

    bool test = e.supprimer(id);
    if (test) {
        ui->letab->setModel(e.afficher());
        QMessageBox::information(nullptr, QObject::tr("Suppression employé"),
                    QObject::tr("Suppression effectuée.\n"
                                "Cliquer OK pour quitter."), QMessageBox::Ok);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Suppression employé"),
                    QObject::tr("Échec de la suppression.\n"
                                "Cliquer OK pour quitter."), QMessageBox::Ok);
    }

    // Effacer le champ de saisie après la suppression
    ui->leid1->clear();
}


void MainWindow::on_clear_clicked() // Cliquer sur le bouton modifier employe
{
    QString idText = ui->leid2->text();
    int id = idText.toInt();  // Convertir l'ID en entier
    QString prenom = ui->leprenom2->text(); // ui:interface utilisateur, leprenom2: widget(QLineEdit)
    QString nom = ui->lenom2->text();  // text() méthode pour retourner le champ sous forme de chaîne de caractères (QString)

    // Vérifier si l'ID est vide
    if (idText.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier employe"),
                    QObject::tr("Employé non modifié. ID invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    // Vérifier si le prénom est vide
    if (prenom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier employe"),
                    QObject::tr("Employé non modifié. Prénom invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    // Vérifier si le nom est vide
    if (nom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier employe"),
                    QObject::tr("Employé non modifié. Nom invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    // Créer un objet employé pour vérifier l'existence de l'ID
    employe e(id, nom, prenom);

    // Vérifier si l'ID existe
    if (!e.existe()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier employe"),
                    QObject::tr("Employé non modifié. ID n'existe pas.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    // Si l'ID existe, procéder à la modification
    if (e.modifier()) {
        QMessageBox::information(nullptr, QObject::tr("Modifier employe"),
                    QObject::tr("Employé modifié.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        ui->letab->setModel(e.afficher()); // Mettre à jour le tableau d'affichage des employés

        // Effacer les champs de saisie après la modification
        ui->leid2->clear();
        ui->leprenom2->clear();
        ui->lenom2->clear();
    }
}

void MainWindow::on_letrie_clicked()
{employe e;
       ui->letab->setModel(e.tri_nom()); //faire le tri par nom
}

void MainWindow::on_letrie2_clicked()
{
    employe e;
           ui->letab->setModel(e.tri_id()); //faire le tri parr id
}

void MainWindow::on_clear_2_clicked()
{
    int CIN = ui->leid2_2->text().toInt();
    QString NOMFORMATION = ui->lenom2_2->text();

    // Vérifier si les champs sont vides
    if (NOMFORMATION.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier formation"),
                    QObject::tr("Formation non modifiée. Nom invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    formateur h(CIN, NOMFORMATION);

    // Vérifier si la formation existe avant de modifier
    if (!h.existe()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier formation"),
                    QObject::tr("Formation non modifiée. CIN invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    // Effectuer la modification
    if (h.modifier()) {
        QMessageBox::information(nullptr, QObject::tr("Modifier formation"),
                    QObject::tr("Modifié.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        ui->letab_2->setModel(h.afficher());

        // Clear les champs de saisie après la modification
        ui->leid2_2->clear();
        ui->lenom2_2->clear();
    }
}


void MainWindow::on_ajout_2_clicked()
{
    // Récupérer les données saisies par l'utilisateur
    QString cinText = ui->leid_2->text();
    QString nomFormation = ui->lenom_2->text();

    // Vérifier que tous les champs sont remplis
    if (cinText.isEmpty() || nomFormation.isEmpty()) {
        QMessageBox::warning(this, QObject::tr("Erreur"), QObject::tr("Tous les champs doivent être remplis."));
        return;
    }

    // Convertir le CIN en entier et vérifier que la conversion est réussie
    bool ok;
    int cin = cinText.toInt(&ok);
    if (!ok || cin <= 0) {
        QMessageBox::warning(this, QObject::tr("Erreur"), QObject::tr("Le CIN doit être un entier positif."));
        return;
    }

    // Créer un objet formateur avec les données validées
    formateur h(cin, nomFormation);

    // Appeler la méthode ajouter et vérifier si l'ajout a réussi
    bool test = h.ajouter();
    if (test) {
        // Mettre à jour la table dans l'interface utilisateur
        ui->letab_2->setModel(h.afficher());
        QMessageBox::information(this, QObject::tr("Succès"), QObject::tr("Ajout effectué.\nCliquez sur OK pour quitter."));
    } else {
        QMessageBox::critical(this, QObject::tr("Erreur"), QObject::tr("Ajout non effectué.\nCliquez sur OK pour quitter."));
    }

    // Nettoyer les champs de saisie après l'ajout
    ui->leid_2->clear();
    ui->lenom_2->clear();
}


void MainWindow::on_affiche_2_clicked()
{
    QSqlQueryModel* model = c.afficher();
    ui->letab_2->setModel(model);
}


void MainWindow::on_supprime_2_clicked() // Function to delete formateur
{
    int CIN = ui->leid1_2->text().toInt(); // Retrieve CIN from input field

    // Check if CIN is valid
    if (CIN <= 0) {
        QMessageBox::warning(nullptr, QObject::tr("Suppression formation"),
                    QObject::tr("CIN invalide. Veuillez entrer un CIN valide.\n"
                                "Cliquer OK pour quitter."), QMessageBox::Ok);
        return;
    }

    formateur c(CIN); // Create a formateur object with the CIN

    if (!c.existe()) { // Check if the formateur exists
        QMessageBox::warning(nullptr, QObject::tr("Suppression formation"),
                    QObject::tr("Échec de la suppression : La formation avec ce CIN n'existe pas.\n"
                                "Cliquer OK pour quitter."), QMessageBox::Ok);
        return;
    }

    bool test = c.supprimer(CIN); // Try to delete the formateur
    if (test) {
        ui->letab_2->setModel(c.afficher()); // Refresh the table view
        QMessageBox::information(nullptr, QObject::tr("Suppression formation"),
                    QObject::tr("Suppression effectuée.\n"
                                "Cliquer OK pour quitter."), QMessageBox::Ok);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Suppression formation"),
                    QObject::tr("Échec de la suppression.\n"
                                "Cliquer OK pour quitter."), QMessageBox::Ok);
    }

    // Clear the input field after deletion
    ui->leid1_2->clear();
}


void MainWindow::on_letrie_2_clicked() //faire le tri far nom de la formation
{
  formateur h;
           ui->letab_2->setModel(h.tri_nomformation());
}

void MainWindow::on_letrie2_2_clicked() //faire tri par id
{
    formateur h;
           ui->letab_2->setModel(h.tri_cin());
}

void MainWindow::on_pushButton_clicked() //fct recherche d'un employé par l'attribu ID
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


void MainWindow::on_pushButton_2_clicked() //fct recherche d'une formation par l'attribu ID
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
        msgBox.setText("Échec de la recherche : Aucun employé trouvé avec cette ID.");
    }

    // Afficher le message dans un pop-up
    msgBox.exec();

     ui->lineEdit_3->clear();

     // Mettre à jour la table avec tous les formateurs après la recherche (refresh ,actualiser
         ui->letab_2->setModel(F1.afficher());  // `afficher()` method to get the full list of formateurs

}

void MainWindow::on_exportpdf_clicked() //expoter le tableau des employé en fichier PDF
{
      e.exportt();
}

void MainWindow::on_pushButton_3_clicked() //fct poour compter nombre des employés
{
    {
       employe F;

        // Appelez la fonction statistique
        QMap<QString, QVariant> statistics = F.getStatistics();

        // Affichez les résultats dans une boîte de dialogue
        QString message = "Statistiques des employes:\n";
        for (auto it = statistics.begin(); it != statistics.end(); ++it) {
            message += QString("%1: %2\n").arg(it.key(), it.value().toString());
        }

        QMessageBox::information(this, "Statistiques", message);

}}
