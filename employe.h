#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class Employe {
public:
    // Constructeur
    Employe();
    Employe(const QString &cin, const QString &nom, const QString &prenom, const QString &ville,
            const QString &poste, const QDate &dateEmbauche, double salaire, const QString &telephone);

    // Méthode pour créer une connexion à la base de données
    bool createEmploye();

    // Getters
    QString getCIN() const;
    QString getNom() const;
    QString getPrenom() const;
    QString getVille() const;
    QString getPoste() const;
    QDate getDateEmbauche() const;
    double getSalaire() const;
    QString getTelephone() const;

    // Setters
    void setCIN(const QString &cin);
    void setNom(const QString &nom);
    void setPrenom(const QString &prenom);
    void setVille(const QString &ville);
    void setPoste(const QString &poste);
    void setDateEmbauche(const QDate &date);
    void setSalaire(double salaire);
    void setTelephone(const QString &telephone);

    // Autres méthodes
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(const QString &cin);
    bool updateEmployee(); // Utilisation de 'updateEmployee' au lieu de 'modifier'
  bool modifier();
private:
    // Attributs de la classe
    QSqlDatabase db;
    QString m_CIN;
    QString m_nom;
    QString m_prenom;
    QString m_ville;
    QString m_poste;
    QDate m_dateEmbauche;
    double m_salaire;
    QString m_telephone;
};

#endif // EMPLOYE_H
