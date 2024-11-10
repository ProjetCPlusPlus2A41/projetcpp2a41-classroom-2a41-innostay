#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"
#include <QList>
#include <QString>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Login_check_PassShowHide_clicked();
    void on_Login_Button_clicked();
    void on_bt_ajouter_clicked();
    void on_bt_modifier_clicked();
    void on_bt_supprimer_clicked();
    void on_comboBox_IDs_currentIndexChanged(int index);
    void on_bt_Tri_Nom_clicked();
    void on_bt_Tri_Gestion_clicked();
    void on_bt_Tri_CIN_clicked();
    void on_bt_ExportPDF_clicked();
    void on_line_Recherche_textChanged(const QString &arg1);

    void on_Menu_Employes_clicked();

    void on_return1_clicked();

private:
    Ui::MainWindow *ui;
    EMPLOYE E;

};
#endif // MAINWINDOW_H
