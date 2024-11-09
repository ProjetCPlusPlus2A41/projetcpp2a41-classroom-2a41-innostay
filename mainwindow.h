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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /* INTEGRATION EMPLOYE */


    /* MENU */


    /* LOGIN */
    void on_Login_Button_clicked();


private:
    Ui::MainWindow *ui;
    EMPLOYE E;

};
#endif // MAINWINDOW_H
