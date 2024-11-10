#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plat.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




//ajouter
void MainWindow::on_pushButton_15_clicked()
{
    int ID = ui->lineEdit_16->text().toInt();
    QString IDD = ui->lineEdit_16->text();
    QString nom = ui->lineEdit_17->text();    // Récupère le nom du plat
    QString type = ui->lineEdit_18->text();    // Récupère le type du plat
    double prix = ui->lineEdit_19->text().toDouble();
    QString prixx = ui->lineEdit_19->text();// Récupère le prix
    QString disponibilite = ui->lineEdit_20->text(); // Récupère la disponibilité

    Plat plat(ID, nom, type, prix, disponibilite);
    if(IDD=="" || nom=="" || type=="" || disponibilite=="" || prixx=="" )
    {
      QMessageBox::warning(this, "Erreur", "veuillez remplir les champs");
    }
    else
    {
        if(disponibilite=="oui" || disponibilite=="non")
        {
            if (plat.ajouter()) {
                QMessageBox::information(this, "Succès", "Plat ajouté avec succès !");
                ui->tableView->setModel(plat.afficher());
            } else {
                QMessageBox::warning(this, "Erreur", "Erreur lors de l'ajout du plat.");
            }
        }
        else
             {
            QMessageBox::warning(this, "Erreur", "le champ disponibilite doit etre(oui/non)");
        }

    }

}

//afficher
void MainWindow::on_pushButton_16_clicked()
{
    Plat p;
    ui->tableView->setModel(p.afficher());
}

//supprimer
void MainWindow::on_pushButton_8_clicked()
{
    int ID = ui->lineEdit_16->text().toInt();
    Plat plat;
    plat.supprimer(ID);
    ui->tableView->setModel(plat.afficher());

}

//modifier
void MainWindow::on_pushButton_7_clicked()
{
    int ID = ui->lineEdit_16->text().toInt();
    QString nom = ui->lineEdit_17->text();    // Récupère le nom du plat
    QString type = ui->lineEdit_18->text();    // Récupère le type du plat
    double prix = ui->lineEdit_19->text().toDouble(); // Récupère le prix
    QString disponibilite = ui->lineEdit_20->text(); // Récupère la disponibilité

    Plat plat(ID, nom, type, prix, disponibilite);
    if (plat.modifier()) {
        QMessageBox::information(this, "Succès", "Plat modifiée avec succès !");
        ui->tableView->setModel(plat.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur lors de la modification du plat.");
    }
}

//doublecick sur le tableau
void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    model = new QSqlTableModel(this);
    model->setTable("PLATS");
    model->select();


    int row = index.row();
    QSqlRecord record = model->record(row);
    QString ID = record.value("ID_RESTAURANT").toString();
    QString nom = record.value("NOM_PLAT").toString();
    QString type = record.value("TYPE").toString();
    QString dispo = record.value("DISPONIBILITE").toString();
    QString prix = record.value("PRIX").toString();

    ui->lineEdit_16->setText(ID);
    ui->lineEdit_17->setText(nom);
    ui->lineEdit_18->setText(type);
    ui->lineEdit_19->setText(prix);
    ui->lineEdit_20->setText(dispo);

}

//trier
void MainWindow::on_pushButton_12_clicked()
{
    Plat p;
    ui->tableView->setModel(p.tri());
}


void MainWindow::on_pushButton_9_clicked()
{
    QSqlQuery query;
    query.exec("SELECT DISPONIBILITE, COUNT(*) FROM PLATS GROUP BY DISPONIBILITE");
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    while (query.next()) {
        QString type = query.value(0).toString();
        int count = query.value(1).toInt();
        QtCharts::QPieSlice *slice = new QtCharts::QPieSlice(type, count);
        series->append(slice);
    }

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Statistics based on PLATS DISPONIBILITE");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->tableView_2);
    chartView->resize(ui->tableView_2->size());
    chartView->show();
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    Plat p;
    ui->tableView->setModel(p.rechercher(arg1));
}


void MainWindow::on_pushButton_11_clicked()
{
    Plat p;
    p.exporterEnPDF();
}


void MainWindow::on_pushButton_13_clicked()
{
    Plat p;
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Choose Image"), QDir::currentPath(), tr("Images (*.png *.jpg *.jpeg *.bmp)"));
    if (imagePath.isEmpty()) {
               return;
           }
           // Read the image file
           QFile file(imagePath);
           if (!file.open(QIODevice::ReadOnly)) {
               qDebug() << "Failed to open image file:" << imagePath;
               return;
           }
    QByteArray imageData = file.readAll();
    int ID = ui->lineEdit_16->text().toInt();
    if (!p.insertImageIntoDatabase(imageData,ID)) {
               qDebug() << "Failed to insert image into database.";
               return;
           }

           qDebug() << "Image inserted into database successfully.";

}


void MainWindow::on_pushButton_17_clicked()
{
    int ID = ui->lineEdit_16->text().toInt();
    QSqlQuery query;
    query.prepare("SELECT image FROM plats WHERE id_restaurant = :id");
    query.bindValue(":id", ID);

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Failed to retrieve image data from database:" ;
        return;
    }

    // Check if a record was found
    if (!query.next()) {
        qDebug() << "No image found for the given ID.";
        return;
    }

    // Retrieve image data from the query result
    QByteArray imageData = query.value("image").toByteArray();

    // Convert image data to QPixmap and display
    QPixmap pixmap;
    pixmap.loadFromData(imageData);

    // Assuming you have a QLabel named imageLabel where you want to display the image
    ui->label_40->setPixmap(pixmap);
    ui->label_40->setScaledContents(true);
}

