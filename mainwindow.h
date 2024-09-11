#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"employe.h"
#include"formateur.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow // declaration des fcts
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajout_clicked();

    void on_affiche_clicked();

    void on_supprime_clicked();

    void on_clear_clicked();

    void on_letrie_clicked();

    void on_letrie2_clicked();

    void on_clear_2_clicked();

    void on_ajout_2_clicked();

    void on_affiche_2_clicked();

    void on_supprime_2_clicked();

    void on_letrie_2_clicked();

    void on_letrie2_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_exportpdf_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    employe e;
    formateur c;
};
#endif // MAINWINDOW_H
