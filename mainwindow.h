#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include <QList>
#include <QString>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bt_ajouter_clicked();

    void on_bt_modifier_clicked();

    void on_bt_supprimer_clicked();

    void on_comboBox_IDs_currentIndexChanged(int index);

    void on_line_Recherche_textChanged(const QString &arg1);

    void on_bt_Tri_Nom_clicked();

    void on_bt_Tri_CIN_clicked();

    void on_bt_ExportPDF_clicked();

private:
    Ui::MainWindow *ui;
    Client C;
};
#endif // MAINWINDOW_H
