#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "reservation.h"
#include <QSqlTableModel>
#include <QCalendarWidget>
#include <QListWidget>
#include <QVBoxLayout>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setTableModel(QSqlQueryModel *model);

private:
    Ui::MainWindow *ui;
    Reservation reservationTemp;
    Reservation reservationManager;

    QCalendarWidget *calendar;
    QListWidget *reservationList;
    QVBoxLayout *mainLayout;
    Reservation reservation;
    QString myString; // Déclaration de la variable globale
    void updateReservationList(const QDate &date);



private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_modifier_clicked();
    void setupDateValidation2();
    void on_dateEdit_dateD_dateChanged(const QDate &date);
    void on_pushButton_triPrix_clicked();
    void setupValidation1();
    void on_pushButton_recherche_clicked();
    void on_pushButton_exportPDF_clicked();
    void on_calendarWidget_clicked(const QDate &date);
    void on_pushButton_Scaner_clicked();
   //  void generateSvgFromList(const QStringList &contentList);


};

#endif // MAINWINDOW_H
