#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QIcon>
#include <QSqlDatabase>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QLabel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);


    // Définir le titre de la fenêtre
    setWindowTitle("Gestion des Employés");

}

MainWindow::~MainWindow() {
    delete ui;
}




void MainWindow::on_Login_Button_clicked()
{
        QString CIN = ui->Login_line_CIN->text();
        QString PASSWORD = ui->Login_line_Password->text();
        QSqlQuery query;
        QString gestion;

        // Execute the query with parameters
        if(query.exec("SELECT * FROM EMPLOYE WHERE CIN='" + CIN + "' AND PASSWORD='" + PASSWORD + "'")) {
            if (query.next()) {
                gestion = query.value(9).toString();  // Assuming 'GESTION' is at index 9 in the EMPLOYE table

                // Set the view based on 'GESTION' role
                ui->stackedWidget->setCurrentIndex(1);
                if (gestion.compare("Administrateur") == 0) {
                    ui->Main_push_Personnel->setEnabled(true);
                    ui->Main_push_Evenement->setEnabled(true);
                    ui->Main_push_Fournisseur->setEnabled(true);
                    ui->Main_push_Locaux->setEnabled(true);
                    ui->Main_push_Sponsoring->setEnabled(true);
                }
                else if (gestion.compare("Personnels") == 0) {
                    ui->Main_push_Personnel->setEnabled(true);
                    ui->Main_push_Evenement->setEnabled(false);
                    ui->Main_push_Fournisseur->setEnabled(false);
                    ui->Main_push_Locaux->setEnabled(false);
                    ui->Main_push_Sponsoring->setEnabled(false);
                }
                else if (gestion.compare("Evenements") == 0) {
                    ui->Main_push_Personnel->setEnabled(false);
                    ui->Main_push_Evenement->setEnabled(true);
                    ui->Main_push_Fournisseur->setEnabled(false);
                    ui->Main_push_Locaux->setEnabled(false);
                    ui->Main_push_Sponsoring->setEnabled(false);
                }
                else if (gestion.compare("Fournisseurs") == 0) {
                    ui->Main_push_Personnel->setEnabled(false);
                    ui->Main_push_Evenement->setEnabled(false);
                    ui->Main_push_Fournisseur->setEnabled(true);
                    ui->Main_push_Locaux->setEnabled(false);
                    ui->Main_push_Sponsoring->setEnabled(false);
                }
                else if (gestion.compare("Locaux") == 0) {
                    ui->Main_push_Personnel->setEnabled(false);
                    ui->Main_push_Evenement->setEnabled(false);
                    ui->Main_push_Fournisseur->setEnabled(false);
                    ui->Main_push_Locaux->setEnabled(true);
                    ui->Main_push_Sponsoring->setEnabled(false);
                }
                else if (gestion.compare("Sponsoring") == 0) {
                    ui->Main_push_Personnel->setEnabled(false);
                    ui->Main_push_Evenement->setEnabled(false);
                    ui->Main_push_Fournisseur->setEnabled(false);
                    ui->Main_push_Locaux->setEnabled(false);
                    ui->Main_push_Sponsoring->setEnabled(true);
                }

                // Set labels for logged-in user information
                QString NOM = query.value(1).toString();    // Assuming 'NOM' is at index 1
                QString PRENOM = query.value(2).toString(); // Assuming 'PRENOM' is at index 2
                ui->Login_label_LoginInfo->setText("Connecté: " + NOM + " " + PRENOM);
                ui->Main_label_LoggedAs->setText("Logged in as: " + NOM + " " + PRENOM + "\nGestion: " + gestion);
            }
            else {
                ui->Login_label_LoginInfo->setText("CIN ou Password sont incorrects");
            }
        }


}
void MainWindow::on_Login_check_PassShowHide_clicked() {
    if (modes == 1) {
        ui->Login_line_Password->setEchoMode(QLineEdit::Normal);
        modes = 0;
    } else {
        ui->Login_line_Password->setEchoMode(QLineEdit::Password);
        modes = 1;
    }
}

void MainWindow::on_pushButton_PDF_clicked() {
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount = ui->tableView->model()->columnCount();

    // Start HTML document
    out << "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           << QString("<title>%1</title>\n").arg("Liste des Employés")
           << "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<center> <H1>Liste des Employés</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

    // Add table headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    out << "<cellspacing=10 cellpadding=3>";
    for (int column = 0; column < columnCount; column++) {
        if (!ui->tableView->isColumnHidden(column)) {
            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    out << "</tr></thead>\n";

    // Add table data
    for (int row = 0; row < rowCount; row++) {
        out << "<tr> <td bkcolor=0>" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView->isColumnHidden(column)) {
                QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }

    // Close HTML document
    out << "</table> </center>\n"
           "</body>\n"
           "</html>\n";

    // Save the generated HTML as PDF
    QString fileName = QFileDialog::getSaveFileName((QWidget*)0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.setPageSize(printer.pageRect().size()); // Necessary to fit the content within page boundaries
    doc.print(&printer);
}

void MainWindow::on_empl_push_ajouter_clicked() {
    QString ID_EMPLOYE = ui->empl_line_id->text();
    QString NOM = ui->empl_line_nom->text();
    QString PRENOM = ui->empl_line_prenom->text();
    QString GENDER = ui->empl_line_sexe->text();
    QString ADRESSE = ui->empl_line_adresse->text();
    QString POSTE = ui->empl_line_poste->text();
    QString EMAIL = ui->empl_line_email->text();
    QString NUM_TEL = ui->empl_line_numtel->text();
    int ABSENCE = ui->empl_line_nbabsance->value();
    QDate D_N = ui->empl_date_DN->date();
    QString PASSWORD = ui->empl_line_mdp->text();

    EMPLOYE E(ID_EMPLOYE, NOM, PRENOM, GENDER, ADRESSE, POSTE, EMAIL, NUM_TEL, ABSENCE, D_N, PASSWORD);
    bool test = E.ajouter();
    if (test) {
        ui->empl_Tableview->setModel(E.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout effectué\nClick Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Ajout non effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::on_comboBox_employe_activated_currentIndexChanged(const QString &arg1) {
    QString ID_EMPLOYE = arg1;
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE ID_EMPLOYE = :ID_EMPLOYE");
    query.bindValue(":ID_EMPLOYE", ID_EMPLOYE);
    if (query.exec()) {
        while (query.next()) {
            ui->empl_line_id_2->setText(query.value(0).toString());
            ui->empl_line_nom_2->setText(query.value(1).toString());
            ui->empl_line_prenom_2->setText(query.value(2).toString());
            ui->empl_line_sexe_2->setText(query.value(3).toString());
            ui->empl_line_adresse_2->setText(query.value(4).toString());
            ui->empl_line_email_2->setText(query.value(5).toString());
            ui->empl_line_poste_2->setText(query.value(6).toString());
            ui->empl_line_numtel2->setText(query.value(7).toString());
            ui->empl_spin_nbabsance_2->setValue(query.value(8).toInt());
            ui->empl_date_DN_2->setDate(query.value(9).toDate());
            ui->empl_line_mdp_2->setText(query.value(10).toString());
        }
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("ECHEC DE chargement"), QMessageBox::Cancel);
    }
}
void MainWindow::on_empl_push_modifier_clicked() {
    QString ID_EMPLOYE = ui->empl_line_id_2->text();
    QString NOM = ui->empl_line_nom_2->text();
    QString PRENOM = ui->empl_line_prenom_2->text();
    QString GENDER = ui->empl_line_sexe_2->text();
    QString ADRESSE = ui->empl_line_adresse_2->text();
    QString POSTE = ui->empl_line_poste_2->text();
    QString EMAIL = ui->empl_line_email_2->text();
    QString NUM_TEL = ui->empl_line_numtel2->text();
    int ABSENCE = ui->empl_spin_nbabsance_2->value();
    QDate D_N = ui->empl_date_DN_2->date();
    QString PASSWORD = ui->empl_line_mdp_2->text();

    EMPLOYE E(ID_EMPLOYE, NOM, PRENOM, GENDER, ADRESSE, POSTE, EMAIL, NUM_TEL, ABSENCE, D_N, PASSWORD);
    bool test = E.modifier();
    if (test) {
        ui->comboBox_employe->setModel(E.afficher());
        ui->empl_Tableview->setModel(E.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Modification effectuée\nClick Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Modification non effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::on_empl_push_supp_clicked() {
    EMPLOYE E;
    E.setID_EMPLOYE(ui->empl_line_supp->text());
    bool test = E.supprimer(E.getID_EMPLOYE());
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectuée\nClick Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Suppression non effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::on_empl_push_refresh_clicked() {
    ui->empl_Tableview->setModel(E.afficher());
}

