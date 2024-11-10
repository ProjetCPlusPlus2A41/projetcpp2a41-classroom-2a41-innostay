#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlTableModel>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlTableModel *model;

private slots:
   /*void on_pushButton7_clicked();  // Modification d'un plat
    void on_pushButton8_clicked();  // Suppression d'un plat
    void on_pushButton9_clicked();  // Ajout d'un plat
    void on_pushButton10_clicked(); // Recherche par prix*/

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_12_clicked();

    void on_pushButton_9_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_17_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
