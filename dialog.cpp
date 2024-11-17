#include "dialog.h"
#include "ui_dialog.h"
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

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
     ui->client_fidelite_combobox->setModel(C.afficher_cin());
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_client_fidelite_combobox_currentIndexChanged(int index)
{
    // Get the selected client's CIN
    QString clientId = ui->client_fidelite_combobox->itemText(index);

    // Query the database for the current points
    QSqlQuery query;
    query.prepare("SELECT PTS_FIDEL FROM CLIENT WHERE CIN = :cin");
    query.bindValue(":cin", clientId);

    if (query.exec() && query.next()) {
        // Set the LineEdit to the retrieved points
        int points = query.value(0).toInt();
        ui->fidelite_lineEdit->setText(QString::number(points));
    } else {
        QMessageBox::warning(this, "Database Error", query.lastError().text());
    }
}

void Dialog::on_plus_pushButton_clicked()
{
    // Get the current client selected in the ComboBox
    QString clientId = ui->client_fidelite_combobox->currentText();

    // Retrieve the current points from the LineEdit
    int currentPoints = ui->fidelite_lineEdit->text().toInt();

    // Increment the points
    currentPoints += 1;

    // Update the LineEdit with the new value
    ui->fidelite_lineEdit->setText(QString::number(currentPoints));

    // Update the database
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET PTS_FIDEL = :points WHERE CIN = :cin");
    query.bindValue(":points", currentPoints);
    query.bindValue(":cin", clientId);

    if (!query.exec()) {
        QMessageBox::warning(this, "Database Error", query.lastError().text());
    }
}


void Dialog::on_moins_pushButton_clicked()
{
    // Get the current client selected in the ComboBox
    QString clientId = ui->client_fidelite_combobox->currentText();

    // Retrieve the current points from the LineEdit
    int currentPoints = ui->fidelite_lineEdit->text().toInt();

    // Decrement the points, ensuring it doesn't go below 0
    if (currentPoints > 0) {
        currentPoints -= 1;

        // Update the LineEdit with the new value
        ui->fidelite_lineEdit->setText(QString::number(currentPoints));

        // Update the database
        QSqlQuery query;
        query.prepare("UPDATE CLIENT SET PTS_FIDEL = :points WHERE CIN = :cin");
        query.bindValue(":points", currentPoints);
        query.bindValue(":cin", clientId);

        if (!query.exec()) {
            QMessageBox::warning(this, "Database Error", query.lastError().text());
        }
    } else {
        QMessageBox::information(this, "Notice", "Points cannot be less than 0.");
    }
}




void Dialog::on_fidel_buttonBox_accepted()
{
        accept(); // This will set the dialog's return value to QDialog::Accepted

}
