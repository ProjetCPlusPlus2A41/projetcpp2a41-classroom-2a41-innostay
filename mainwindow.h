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
private slots:
    void on_addEmployeeButton_clicked();
    void on_deleteEmployeeButton_clicked();
    void on_viewEmployeeButton_clicked();
    void on_updateEmployeeButton_clicked();
    void on_modifierButton_clicked(); // Ajoutez cette ligne

private:
    void setupLayout(QWidget *parent);
    void loadEmployeeTable();
    void addEmployee(const Employe &employe);
    void updateEmployee(const QString &cin, const Employe &employe); // Méthode pour mettre à jour un employé
    void deleteEmployee(const QString &cin);
    Employe getEmployee(int cin); // Notez que nous utilisons QString ici

    QList<Employe> employees;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
