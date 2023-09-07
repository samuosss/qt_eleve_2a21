#ifndef ACTIVITE_H
#define ACTIVITE_H

#include <QDialog>
#include <QWidget>
#include<QString>
#include<QSqlQueryModel>
#include<QDate>  // Include QDate header
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

class activite  // Renamed the class to 'activite'
{
public:

    activite() {
        id_ac = "";
        nom_dac = "";
        type_dac = "";
        date_dac = QDate::currentDate(); // Initialize date_dac to current date
    }

    bool ajouter();
    QSqlQueryModel* afficher();
    void setNom(const QString& newNom) {
        nom_dac = newNom;
    }

    QString getNom() const {
        return nom_dac;
    }

    void setType(const QString& newType) {
        type_dac = newType;
    }

    QString getType() const {
        return type_dac;
    }

    void setId(const QString& newId) {
        id_ac = newId;
    }

    QString getId() const {
        return id_ac;
    }

    void setDate(const QDate& newDate) {
        date_dac = newDate;
    }

    QDate getDate() const {
        return date_dac;
    }

    bool supprimer(QString id);
    bool modifier();
    bool controlnumber(QString);
    bool controlstring(QString);
    QSqlQueryModel* recherche(int i, QString s);
    QSqlQueryModel* sort(int);
    void exportpdf(QString s);
    activite(QString id, QString nom, QString type, QDate date) {
        this->id_ac = id;
        this->nom_dac = nom;
        this->type_dac = type;
        this->date_dac = date;
    }

private:
    QString nom_dac, type_dac, id_ac;
    QDate date_dac;
};

#endif
