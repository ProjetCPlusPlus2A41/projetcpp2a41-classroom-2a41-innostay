#ifndef RESETPASS_H
#define RESETPASS_H
#include "smtp.h"
#include <QDialog>

namespace Ui {
class Resetpass;
}

class Resetpass : public QDialog
{
    Q_OBJECT

public:
    explicit Resetpass(QWidget *parent = nullptr);
    ~Resetpass();

private slots:
    void on_SendOTP_clicked();

    void on_Confirmer_clicked();

private:
    Ui::Resetpass *ui;
};

#endif // RESETPASS_H
