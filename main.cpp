#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "reservation.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Starting application...";

    Connection c;
    if (!c.createconnect()) {
        qDebug() << "Database connection failed.";
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
                              QObject::tr("Failed to connect to the database.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return -1;
    }

    qDebug() << "Database connected successfully.";

    MainWindow w;
    Reservation reservationTemp;

    QSqlQueryModel *model = reservationTemp.afficher();
    if (model) {
        w.setTableModel(model);
        qDebug() << "Reservation model set successfully.";
    } else {
        qDebug() << "Failed to retrieve reservation model.";
    }

    w.show();
    return a.exec();
}
