#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QIcon>
#include <QSqlDatabase>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QLabel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);


    // Définir le titre de la fenêtre
    setWindowTitle("Gestion des Employés");

connect(ui->updateEmployeeButton, &QPushButton::clicked, this, &MainWindow::on_updateEmployeeButton_clicked);

connect(ui->modifierButton, &QPushButton::clicked, this, &MainWindow::on_modifierButton_clicked);

    loadEmployeeTable();

    // Définir les icônes pour les boutons
    ui->exportButton->setIcon(QIcon(":/images/ressource/exporter (1).png"));
    ui->facialRecognitionButton->setIcon(QIcon(":/images/ressource/la-reconnaissance-faciale (1).png"));
    ui->searchButton->setIcon(QIcon(":/images/ressource/loupe (3).png"));
    ui->passwordButton->setIcon(QIcon(":/images/ressource/mot-de-passe (1).png"));
    ui->emergencyContactButton->setIcon(QIcon(":/images/ressource/personne-a-contacter-en-cas-durgence (1).png"));
    ui->statisticsButton->setIcon(QIcon(":/images/ressource/statistiques (1).png"));
    ui->sortButton->setIcon(QIcon(":/images/ressource/tri 2 (1).png"));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadEmployeeTable() {
    Employe emp;
    QSqlQueryModel *model = emp.afficher(); // Vérifiez que la méthode afficher() retourne un QSqlQueryModel*
    ui->employeeTableView->setModel(model);  // Assurez-vous que employeeTableView existe dans votre interface
}

void MainWindow::on_addEmployeeButton_clicked() {
    // Récupérer les données des champs d'entrée
    QString cin = ui->cinLineEdit->text();
    QString nom = ui->nomLineEdit->text();
    QString prenom = ui->prenomLineEdit->text();
    QString ville = ui->villeLineEdit->text();
    QString poste = ui->posteLineEdit->text();
    QDate dateEmbauche = ui->dateEmbaucheDateEdit->date();
    double salaire = ui->salaireSpinBox->value();
    QString telephone = ui->telephoneLineEdit->text();

    // Créer un nouvel employé
    Employe nouvelEmploye(cin, nom, prenom, ville, poste, dateEmbauche, salaire, telephone);

    // Appeler la méthode ajouter() de Employe pour l'ajout dans la base de données
    if (nouvelEmploye.ajouter()) {
        QMessageBox::information(this, "Succès", "Employé ajouté avec succès !");
        loadEmployeeTable();  // Rafraîchit la vue après l'ajout
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur lors de l'ajout de l'employé !");
    }
}

void MainWindow::on_deleteEmployeeButton_clicked() {
    QString cin = ui->cinLineEdit->text();  // Récupérer le CIN de l'employé à supprimer

    // Créer un objet Employe pour utiliser la méthode supprimer
    Employe emp;
    if (emp.supprimer(cin)) {
        QMessageBox::information(this, "Succès", "Employé supprimé avec succès !");
        loadEmployeeTable();  // Rafraîchit la vue après la suppression
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur lors de la suppression de l'employé !");
    }
}

void MainWindow::on_updateEmployeeButton_clicked() {
    QString cin = ui->cinLineEdit->text();

    // Récupérer les nouvelles données depuis l'interface
    QString nom = ui->nomLineEdit->text();
    QString prenom = ui->prenomLineEdit->text();
    QString ville = ui->villeLineEdit->text();
    QString poste = ui->posteLineEdit->text();
    QDate dateEmbauche = ui->dateEmbaucheDateEdit->date();
    double salaire = ui->salaireSpinBox->value();
    QString telephone = ui->telephoneLineEdit->text();

    // Créer l'objet Employe avec les nouvelles informations
    Employe updatedEmploye(cin, nom, prenom, ville, poste, dateEmbauche, salaire, telephone);

    // Appeler la méthode updateEmployee() pour la mise à jour
    if (updatedEmploye.updateEmployee()) {
        QMessageBox::information(this, "Succès", "Employé mis à jour avec succès !");
        loadEmployeeTable();  // Rafraîchit la vue après la mise à jour
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur lors de la mise à jour de l'employé !");
    }
}

void MainWindow::on_viewEmployeeButton_clicked() {
    QString cin = ui->cinLineEdit->text(); // Récupérer le CIN de l'employé à afficher

    bool ok;
    int cinInt = cin.toInt(&ok); // Conversion du CIN en entier
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "Le CIN doit être un nombre valide !");
        return; // Sortie si la conversion échoue
    }

    // Charger les informations de l'employé pour affichage
    Employe emp = getEmployee(cinInt); // Supposons que getEmployee prend un int
    if (!emp.getCIN().isEmpty()) { // Vérifier si un employé a été trouvé
        ui->nomLineEdit->setText(emp.getNom());
        ui->prenomLineEdit->setText(emp.getPrenom());
        ui->villeLineEdit->setText(emp.getVille());
        ui->posteLineEdit->setText(emp.getPoste());
        ui->dateEmbaucheDateEdit->setDate(emp.getDateEmbauche());
        ui->salaireSpinBox->setValue(emp.getSalaire());
        ui->telephoneLineEdit->setText(emp.getTelephone());
    } else {
        QMessageBox::warning(this, "Erreur", "Employé non trouvé !");
    }
}

Employe MainWindow::getEmployee(int cin) {
    Employe emp; // Crée un employé vide
    QSqlQuery query;
    query.prepare("SELECT * FROM employes WHERE CIN = :CIN");
    query.bindValue(":CIN", cin);

    if (query.exec() && query.next()) {
        emp.setCIN(query.value("CIN").toString());
        emp.setNom(query.value("nom").toString());
        emp.setPrenom(query.value("prenom").toString());
        emp.setVille(query.value("ville").toString());
        emp.setPoste(query.value("poste").toString());
        emp.setDateEmbauche(query.value("dateEmbauche").toDate());
        emp.setSalaire(query.value("salaire").toDouble());
        emp.setTelephone(query.value("telephone").toString());
    } else {
        QMessageBox::warning(this, "Erreur", "Employé non trouvé !");
    }

    return emp;
}
void MainWindow:: on_modifierButton_clicked() {
    QString cin = ui->cinLineEdit->text();  // Récupérer le CIN de l'employé à mettre à jour

    // Récupérer les nouvelles données depuis l'interface
    QString nom = ui->nomLineEdit->text();
    QString prenom = ui->prenomLineEdit->text();
    QString ville = ui->villeLineEdit->text();
    QString poste = ui->posteLineEdit->text();
    QDate dateEmbauche = ui->dateEmbaucheDateEdit->date();
    double salaire = ui->salaireSpinBox->value();
    QString telephone = ui->telephoneLineEdit->text();

    // Créer l'objet Employe avec les nouvelles informations
    Employe updatedEmploye(cin, nom, prenom, ville, poste, dateEmbauche, salaire, telephone);

    // Appeler la méthode modifier() de Employe pour la mise à jour
    if (updatedEmploye.modifier()) {
        QMessageBox::information(this, "Succès", "Employé mis à jour avec succès !");
        loadEmployeeTable();  // Rafraîchit la vue après la mise à jour
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur lors de la mise à jour de l'employé !");
    }
}

