#ifndef ELEVE_H
#define ELEVE_H

#include <QDialog>

#include <QWidget>
#include<QString>
#include<QSqlQueryModel>
#include<QTime>
#include<QApplication>
#include<QtWidgets/QMainWindow>
#include<QtCharts/QChartView>
#include<QtCharts/QBarSeries>
#include<QtCharts/QBarSet>
#include<QtCharts/QLegend>
#include<QtCharts/QBarCategoryAxis>
#include<QtCharts/QHorizontalBarSeries>
#include<QtCharts/QLineSeries>
#include<QtCharts/QCategoryAxis>
#include<QtCharts/QPieSeries>
#include<QtCharts/QPieSlice>
#include <QSqlQuery>
#include <QtDebug>
#include <QVariant>
#include <QPainter>
#include <QDesktopServices>
#include <QPdfWriter>
#include <QModelIndex>
#include <QUrl>
#include <vector>
#include <QMessageBox>
#include <QUrl>
#include <QKeySequenceEdit>
#include <QDebug>

QT_CHARTS_USE_NAMESPACE


class eleve
{
public:

    eleve(){
        id="";
        nom="";
        prenom="";
        niveauscolaire="";
        id_activite="";
    };

    bool ajouter();
    QSqlQueryModel* afficher();
    void setNom(const QString& newNom) {
            nom = newNom;
        }

        QString getNom() const {
            return nom;
        }

        void setPrenom(const QString& newPrenom) {
            prenom = newPrenom;
        }

        QString getPrenom() const {
            return prenom;
        }

        void setId(const QString& newId) {
            id = newId;
        }

        QString getId() const {
            return id;
        }

        void setNiveauScolaire(const QString& newNiveauScolaire) {
            niveauscolaire = newNiveauScolaire;
        }

        QString getNiveauScolaire() const {
            return niveauscolaire;
        }
    bool supprimer(QString id);
    bool modifier();
    bool controlnumber(QString);
    bool controlstring(QString);
    QSqlQueryModel * recherche(int i,QString s);
    QSqlQueryModel * sort(int);
    void exportpdf(QString s);
    eleve(QString id,QString name ,QString prenom,QString niv,QString id_activite){
        this->id=id;
        this->nom=name;
        this->prenom=prenom;
        this->niveauscolaire=niv;
        this->id_activite=id_activite;

    };

   private:
    QString nom,prenom,id,niveauscolaire,id_activite;

};
#endif
