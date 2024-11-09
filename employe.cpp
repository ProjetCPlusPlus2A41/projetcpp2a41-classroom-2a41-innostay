#include "employe.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDebug>
#include <QVariant>

// Constructeur par défaut
Employe::Employe() {}

Employe::Employe(const QString &cin, const QString &nom, const QString &prenom, const QString &ville,
                 const QString &poste, const QDate &dateEmbauche, double salaire, const QString &telephone)
    : m_CIN(cin), m_nom(nom), m_prenom(prenom), m_ville(ville),
      m_poste(poste), m_dateEmbauche(dateEmbauche), m_salaire(salaire), m_telephone(telephone) {}

// Getters
QString Employe::getCIN() const { return m_CIN; }
QString Employe::getNom() const { return m_nom; }
QString Employe::getPrenom() const { return m_prenom; }
QString Employe::getVille() const { return m_ville; }
QString Employe::getPoste() const { return m_poste; }
QDate Employe::getDateEmbauche() const { return m_dateEmbauche; }
double Employe::getSalaire() const { return m_salaire; }
QString Employe::getTelephone() const { return m_telephone; }

// Setters
void Employe::setCIN(const QString &cin) { m_CIN = cin; }
void Employe::setNom(const QString &nom) { m_nom = nom; }
void Employe::setPrenom(const QString &prenom) { m_prenom = prenom; }
void Employe::setVille(const QString &ville) { m_ville = ville; }
void Employe::setPoste(const QString &poste) { m_poste = poste; }
void Employe::setDateEmbauche(const QDate &date) { m_dateEmbauche = date; }
void Employe::setSalaire(double salaire) { m_salaire = salaire; }
void Employe::setTelephone(const QString &telephone) { m_telephone = telephone; }

bool Employe::createEmploye() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("employes.db");

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données : " << db.lastError().text();
        return false;
    }
    qDebug() << "Connexion à la base de données réussie.";
    return true;
}

// Ajouter un employé dans la base de données
bool Employe::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO employes (CIN, nom, prenom, ville, poste, dateEmbauche, salaire, telephone) "
                  "VALUES (:CIN, :nom, :prenom, :ville, :poste, :dateEmbauche, :salaire, :telephone)");
    query.bindValue(":CIN", m_CIN);
    query.bindValue(":nom", m_nom);
    query.bindValue(":prenom", m_prenom);
    query.bindValue(":ville", m_ville);
    query.bindValue(":poste", m_poste);
    query.bindValue(":dateEmbauche", m_dateEmbauche);
    query.bindValue(":salaire", m_salaire);
    query.bindValue(":telephone", m_telephone);

    return query.exec();
}

// Afficher les employés
QSqlQueryModel* Employe::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employes");
    return model;
}

// Supprimer un employé par CIN
bool Employe::supprimer(const QString &cin) {
    QSqlQuery query;
    query.prepare("DELETE FROM employes WHERE CIN = :CIN");
    query.bindValue(":CIN", cin);
    return query.exec();
}

// Mettre à jour un employé par CIN
bool Employe::updateEmployee() { // Changement de nom ici
    QSqlQuery query;
    query.prepare("UPDATE employes SET nom = :nom, prenom = :prenom, ville = :ville, poste = :poste, "
                  "dateEmbauche = :dateEmbauche, salaire = :salaire, telephone = :telephone "
                  "WHERE CIN = :CIN");
    query.bindValue(":CIN", m_CIN);
    query.bindValue(":nom", m_nom);
    query.bindValue(":prenom", m_prenom);
    query.bindValue(":ville", m_ville);
    query.bindValue(":poste", m_poste);
    query.bindValue(":dateEmbauche", m_dateEmbauche);
    query.bindValue(":salaire", m_salaire);
    query.bindValue(":telephone", m_telephone);

    return query.exec();
}
bool Employe::modifier() {
    QSqlQuery query;
    query.prepare("UPDATE employes SET nom = :nom, prenom = :prenom, ville = :ville, poste = :poste, "
                  "dateEmbauche = :dateEmbauche, salaire = :salaire, telephone = :telephone WHERE CIN = :cin");
    query.bindValue(":CIN", m_CIN);
    query.bindValue(":nom", m_nom);
    query.bindValue(":prenom", m_prenom);
    query.bindValue(":ville", m_ville);
    query.bindValue(":poste", m_poste);
    query.bindValue(":dateEmbauche", m_dateEmbauche);
    query.bindValue(":salaire", m_salaire);
    query.bindValue(":telephone", m_telephone);
    return query.exec();  // Exécute la requête et retourne true si elle réussit
}
