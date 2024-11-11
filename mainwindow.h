#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "reservation.h"
#include <QSqlTableModel>

namespace Ui {
class MainWindow; // Déclaration de la classe Ui::MainWindow
}



class MainWindow : public QMainWindow {
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
      void setTableModel(QSqlQueryModel *model); // Déclaration de la méthode

private:
    Ui::MainWindow *ui;
    Reservation reservationTemp; // Déclaration de reservationTemp

private slots:
    void on_pushButton_ajouter_clicked(); // Slot pour le bouton Ajouter
    void on_pushButton_supprimer_clicked(); // Slot pour le bouton Supprimer
     void on_pushButton_modifier_clicked(); // Ajoutez cette ligne
     void setupValidation();
     void setupDateValidation();
     void on_dateEdit_dateD_changed(const QDate &date);



};

#endif // MAINWINDOW_H
