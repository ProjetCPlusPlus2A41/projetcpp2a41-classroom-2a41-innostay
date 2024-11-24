#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include <QList>
#include <QString>
#include <QSqlQuery>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

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


    void on_bt_stat_clicked();

    QChartView* Client_choix_pie();

    void on_bt_points_clicked();

private:
    Ui::MainWindow *ui;
    Client C;
};
#endif // MAINWINDOW_H
