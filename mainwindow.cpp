#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reservation.h" // Assurez-vous d'inclure votre fichier d'en-tête Reservation
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QTableWidget>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include "qrcode.h"
#include "qrwidget.h"
#include <fstream>
#include <QSvgRenderer>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this); // Initialise l'interface utilisateur
}

MainWindow::~MainWindow()
{
    delete ui; // Libère la mémoire de l'interface utilisateur
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
void MainWindow::setupValidation1()
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

void MainWindow::setupDateValidation2()
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
void MainWindow::on_dateEdit_dateD_dateChanged(const QDate &date) {
    // Vérifiez si la date saisie est antérieure à la date actuelle
    if (date < QDate::currentDate()) {
        QMessageBox::warning(this, "Date invalide", "La date ne peut pas être antérieure à la date actuelle.");
        ui->dateEdit_dateD->setDate(QDate::currentDate());
    }
}


void MainWindow::on_pushButton_triPrix_clicked()
{
    // Création d'un modèle pour afficher les données triées
    QSqlTableModel *model = reservationTemp.afficher(); // Assurez-vous que cette méthode retourne un QSqlTableModel*

    if (model) {
        model->setSort(4, Qt::DescendingOrder); // 4 est l'index de la colonne "PRIX", tri décroissant
        model->select(); // Sélectionnez à nouveau pour appliquer le tri
        ui->tableView->setModel(model); // Mettre à jour la vue
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les données.");
    }
}

void MainWindow::on_pushButton_recherche_clicked() {
    // Récupérer l'ID saisi
    bool ok;
    int idRecherche = ui->L1->text().toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    // Utiliser la fonction de recherche dans Reservation
    QSqlTableModel *model = reservationTemp. rechercherParID(idRecherche);

    if (model) {
        ui->tableView->setModel(model); // Afficher les résultats dans la vue
    } else {
        // Si aucune donnée n'est trouvée
        QMessageBox::warning(this, "ID Inexistant", "L'ID recherché n'existe pas.");
    }
}

void MainWindow::on_pushButton_exportPDF_clicked()
{
    // Vérifier si le modèle est défini
    QAbstractItemModel* model = ui->tableView->model();
    if (!model) {
        QMessageBox::warning(this, "Erreur", "Aucun modèle associé à la table !");
        return;
    }

    // Ouvrir une boîte de dialogue pour sélectionner le fichier
    QString filePath = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "*.pdf");
    if (filePath.isEmpty()) {
        return; // Annuler si l'utilisateur ne choisit pas de chemin
    }

    // Configurer le PDF
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4)); // Format A4
    pdfWriter.setPageMargins(QMarginsF(20, 20, 20, 20)); // Marges : 20 pixels

    QPainter painter(&pdfWriter);

    // Récupérer les dimensions de la page A4
    int pageWidth = pdfWriter.width();  // Largeur de la page
    int pageHeight = pdfWriter.height(); // Hauteur de la page

    // Dessiner le titre
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    QRect titleRect(0, 0, pageWidth, 50); // Rectangle pour le titre
    painter.drawText(titleRect, Qt::AlignCenter, "Exportation du Tableau"); // Titre centré

    // Ajout d'espace sous le titre
    int titleHeight = 70; // Réservez un espace de 70 pixels pour le titre

    // Dimensions dynamiques pour les cellules
    int cols = model->columnCount(); // Nombre de colonnes
    int rows = model->rowCount();    // Nombre de lignes

    int cellWidth = pageWidth / cols;        // Largeur ajustée dynamiquement en fonction du nombre de colonnes
    int cellHeight = (pageHeight - titleHeight - 50) / (rows + 1); // Hauteur ajustée

    // Limiter la hauteur minimale à 30 pixels
    if (cellHeight < 30) {
        cellHeight = 30;
    }

    // Début des coordonnées du tableau
    int startY = titleHeight; // Commence sous le titre

    // Dessiner les en-têtes de colonnes
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    for (int col = 0; col < cols; ++col) {
        QRect rect(col * cellWidth, startY, cellWidth, cellHeight);
        painter.drawRect(rect);
        QString header = model->headerData(col, Qt::Horizontal).toString();
        painter.drawText(rect, Qt::AlignCenter, header);
    }

    // Dessiner les données du tableau
    painter.setFont(QFont("Arial", 10));
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            QRect rect(col * cellWidth, startY + (row + 1) * cellHeight, cellWidth, cellHeight);
            painter.drawRect(rect);
            QString data = model->data(model->index(row, col)).toString();
            painter.drawText(rect, Qt::AlignCenter, data);
        }
    }

    // Terminer le dessin
    painter.end();

    // Confirmation
    QMessageBox::information(this, "Succès", "Le tableau a été exporté avec succès en PDF !");
};

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    QSqlQuery query;

    // Préparer la requête SQL avec TO_DATE pour comparer les dates
    query.prepare("SELECT ID, ETAT, DATE_D, DATE_F, PRIX, ID_CLIENT "
                  "FROM RESERVATION "
                  "WHERE DATE_D <= TO_DATE(:currentDate, 'YYYY-MM-DD') "
                  "AND DATE_F >= TO_DATE(:currentDate, 'YYYY-MM-DD')");

    // Convertir la date en format string pour la passer à la requête SQL
    query.bindValue(":currentDate", date.toString("yyyy-MM-dd"));

    // Exécuter la requête
    if (!query.exec()) {
        QMessageBox::critical(this, "Query Error", "Erreur lors de l'exécution de la requête.");
        return;
    }

    // Vider le QListWidget avant d'ajouter les nouvelles réservations
    ui->listWidget->clear();

    // Flag pour vérifier si des réservations ont été trouvées
    bool foundReservations = false;

    // Parcourir les résultats de la requête et les ajouter au QListWidget
    while (query.next()) {
        int id = query.value("ID").toInt();
        QString etat = query.value("ETAT").toString();
        QDate dateD = query.value("DATE_D").toDate();
        QDate dateF = query.value("DATE_F").toDate();
        double prix = query.value("PRIX").toDouble();
        int idClient = query.value("ID_CLIENT").toInt();

        // Créer une ligne descriptive pour chaque réservation
        QString reservation = QString("ID: %1    État: %2    Date de début: %3    Date de fin: %4    Prix: %.2f €    Client ID: %5")
                                      .arg(id)
                                      .arg(etat)
                                      .arg(dateD.toString("dd/MM/yyyy"))
                                      .arg(dateF.toString("dd/MM/yyyy"))
                                      .arg(prix, 0, 'f', 2)  // Affiche le prix avec 2 décimales
                                      .arg(idClient);

     ///   ui->

        // Ajouter la réservation au QListWidget
        ui->listWidget->addItem(reservation);

        // Marquer que des réservations ont été trouvées
        foundReservations = true;
    }

    // Si aucune réservation n'est trouvée, afficher un message
    if (!foundReservations) {
        QMessageBox::information(this, "Aucune réservation", "Aucune réservation trouvée pour cette date.");
    }
}

void MainWindow::on_pushButton_Scaner_clicked()
{
    // Vérifiez s'il y a un élément sélectionné dans le QListWidget
    QListWidgetItem *selectedItem = ui->listWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner une réservation dans la liste.");
        return;
    }
    QString myString = selectedItem->text();
    const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(myString.toStdString().c_str(), qrcodegen::QrCode::Ecc::LOW);
    // Sauvegarder le QR code en format SVG
    std::ofstream myfile;
    myfile.open("qrcode.svg");
    myfile << qr.toSvgString(4); // Échelle augmentée pour meilleure qualité
    myfile.close();
    // Charger et afficher le QR code dans un QLabel
    QSvgRenderer svgRenderer(QString("qrcode.svg"));
    QPixmap pix(QSize(150, 150)); // Taille de l'image
    pix.fill(Qt::transparent);   // Assurez une transparence pour un rendu propre
    QPainter pixPainter(&pix);
    pixPainter.setRenderHint(QPainter::Antialiasing);
    svgRenderer.render(&pixPainter);
    pixPainter.end();
    ui->label_2->setPixmap(pix);

      QMessageBox::information(this, "Succès", "Le code QR a été généré et affiché avec succès !");

}

