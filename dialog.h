#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "client.h"
#include <QList>
#include <QString>
#include <QSqlQuery>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_client_fidelite_combobox_currentIndexChanged(int index);
    
    void on_plus_pushButton_clicked();

    void on_moins_pushButton_clicked();

    void on_fidel_buttonBox_accepted();

private:
    Ui::Dialog *ui;
    Client C;
};

#endif // DIALOG_H
