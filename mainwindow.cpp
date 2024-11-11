#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reservation.h" // Assurez-vous d'inclure votre fichier d'en-tête Reservation
#include <QMessageBox>


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupValidation();
    setupDateValidation();

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setTableModel(QSqlQueryModel *model) {
    // Implémentation de la méthode
    // Par exemple, vous pouvez configurer une vue ici
    ui->tableView->setModel(model);}

void MainWindow::on_pushButton_ajouter_clicked()
{
    // Récupération des informations saisies
    int id = ui->lineEdit_ID->text().toInt(); // Assurez-vous que ce champ existe
    QString etat = ui->comboBox_etat->currentText(); // Récupérer la valeur sélectionnée dans le QComboBox
    QDate dateD = ui->dateEdit_dateD->date(); // Récupérer la date de début depuis QDateEdit
    QDate dateF = ui->dateEdit_dateF->date(); // Récupérer la date de fin depuis QDateEdit

    // Vérification que le champ prix n'est pas vide
    if (ui->lineEdit_prix->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le champ prix ne peut pas être vide. Veuillez entrer une valeur.");
        ui->lineEdit_prix->clear(); // Optionnel : effacer le champ
        return; // Sortir de la fonction si le champ est vide
    }

    // Récupération du prix après vérification
    int prix = ui->lineEdit_prix->text().toInt();

    // Vérification que le champ idClient n'est pas vide
    if (ui->lineEdit_idClient->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le champ ID Client ne peut pas être vide. Veuillez entrer une valeur.");
        ui->lineEdit_idClient->clear();
        return; // Sortir de la fonction si le champ est vide
    }

    int idClient = ui->lineEdit_idClient->text().toInt(); // Assurez-vous que ce champ existe

    // Instanciation d'un objet Reservation
    Reservation reservationTemp(id, etat, dateD, dateF, prix, idClient);

    // Ajouter la réservation
    bool test = reservationTemp.ajouter();

    if (test) // Si l'ajout a réussi
    {
        // Actualiser l'affichage
        ui->tableView->setModel(reservationTemp.afficher());

        QMessageBox::information(this, tr("OK"),
                                 tr("Ajout effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
    else // Si l'ajout a échoué
    {
        QMessageBox::critical(this, tr("Not OK"),
                              tr("Ajout non effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    // Vérifier si le champ d'ID est vide
    if (ui->lineEditIDS->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le champ ID ne peut pas être vide. Veuillez entrer un ID.");
        ui->lineEditIDS->clear(); // Optionnel : effacer le champ
        return; // Sortir de la fonction si le champ est vide
    }

    int id = ui->lineEditIDS->text().toInt(); // Récupérer l'ID saisi

    // Appeler la méthode supprimer()
    bool test = reservationTemp.supprimer(id);

    if (test) // Si la suppression a réussi
    {
        // Actualiser l'affichage
        ui->tableView->setModel(reservationTemp.afficher()); // Appeler la méthode afficher() pour mettre à jour le modèle

        QMessageBox::information(this, tr("OK"),
                                 tr("Suppression effectuée\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else // Si la suppression a échoué
    {
        QMessageBox::critical(this, tr("Not OK"),
                              tr("Suppression non effectuée.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::on_pushButton_modifier_clicked()
{
    // Vérification que le champ d'ID n'est pas vide
    if (ui->lineEdit_ID_2->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le champ ID ne peut pas être vide. Veuillez entrer un ID.");
        ui->lineEdit_ID_2->clear(); // Optionnel : effacer le champ
        return; // Sortir de la fonction si le champ est vide
    }

    // Vérification que le champ prix n'est pas vide
    if (ui->lineEdit_prix_2->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le champ prix ne peut pas être vide. Veuillez entrer une valeur.");
        ui->lineEdit_prix_2->clear(); // Optionnel : effacer le champ
        return; // Sortir de la fonction si le champ est vide
    }

    // Vérification que le champ idClient n'est pas vide
    if (ui->lineEdit_idClient_2->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le champ ID Client ne peut pas être vide. Veuillez entrer une valeur.");
        ui->lineEdit_idClient_2->clear(); // Optionnel : effacer le champ
        return; // Sortir de la fonction si le champ est vide
    }

    // Récupération des informations saisies
    int id = ui->lineEdit_ID_2->text().toInt();
    QString etat = ui->comboBox_etat_2->currentText();
    QDate dateD = ui->dateEdit_dateD_2->date();
    QDate dateF = ui->dateEdit_dateF_2->date();
    int prix = ui->lineEdit_prix_2->text().toInt();
    int idClient = ui->lineEdit_idClient_2->text().toInt();

    Reservation reservation; // Instanciation d'un objet Reservation

    // Appel à la méthode modifier avec tous les bons arguments
    bool test = reservation.modifier(id, etat, dateD, dateF, prix, idClient);

    if (test)
    {
        ui->tableView->setModel(reservation.afficher()); // Actualiser l'affichage
        QMessageBox::information(this, tr("OK"), tr("Modification effectuée."), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(this, tr("Not OK"), tr("Modification non effectuée."), QMessageBox::Cancel);
    }
}

void MainWindow::setupValidation()
{
    // Crée un validateur pour accepter uniquement des entiers entre 0 et 9999 (4 chiffres maximum)
    QIntValidator *validator = new QIntValidator(0, 9999, this);

    // Applique le validateur au QLineEdit
    ui->lineEdit_ID->setValidator(validator);

    // Applique le validateur au QLineEdit
    ui->lineEdit_ID_2->setValidator(validator);

    // Applique le validateur au QLineEdit
    ui->lineEditIDS->setValidator(validator);

    ui->lineEdit_idClient->setValidator(validator);



}

void MainWindow::setupDateValidation()
{
    // Plage de dates : Min = aujourd'hui, Max = 1 an dans le futur
    ui->dateEdit_dateD->setMinimumDate(QDate::currentDate()); // Date minimale = aujourd'hui

    // Facultatif : Définir le format de la date pour une saisie claire
    ui->dateEdit_dateD->setDisplayFormat("yyyy-MM-dd");

    // Plage de dates : Min = aujourd'hui, Max = 1 an dans le futur
    ui->dateEdit_dateF->setMinimumDate(QDate::currentDate()); // Date minimale = aujourd'hui

    // Facultatif : Définir le format de la date pour une saisie claire
    ui->dateEdit_dateF->setDisplayFormat("yyyy-MM-dd");

    // Plage de dates : Min = aujourd'hui, Max = 1 an dans le futur
    ui->dateEdit_dateD_2->setMinimumDate(QDate::currentDate()); // Date minimale = aujourd'hui

    // Facultatif : Définir le format de la date pour une saisie claire
    ui->dateEdit_dateD_2->setDisplayFormat("yyyy-MM-dd");

    // Plage de dates : Min = aujourd'hui, Max = 1 an dans le futur
    ui->dateEdit_dateF_2->setMinimumDate(QDate::currentDate()); // Date minimale = aujourd'hui

    // Facultatif : Définir le format de la date pour une saisie claire
    ui->dateEdit_dateF_2->setDisplayFormat("yyyy-MM-dd");



}


// Événement déclenché lors du changement de la date dans le QDateEdit
void MainWindow::on_dateEdit_dateD_changed(const QDate &date) {
    // Vérifiez si la date saisie est antérieure à la date actuelle
    if (date < QDate::currentDate()) {
        QMessageBox::warning(this, "Date invalide", "La date ne peut pas être antérieure à la date actuelle.");
        ui->dateEdit_dateD->setDate(QDate::currentDate());
    }
}
