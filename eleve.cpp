#include "eleve.h"
#include "connexion.h"

bool eleve::ajouter() {
    QSqlQuery query;

    query.prepare("INSERT INTO ELEVE (ID, NOM, PRENOM, NIVEAU, Id_activite) "
                  "VALUES (:ID, :NOM, :PRENOM, :NIVEAU, :ID_ACTIVITE)");
    query.bindValue(":ID", id);
    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":NIVEAU", niveauscolaire);
    query.bindValue(":ID_ACTIVITE", id_activite);

    return query.exec();
}

QSqlQueryModel *eleve::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM eleve");
    return model;
}

bool eleve::supprimer(QString id) {
    QSqlQuery query;

    query.prepare("DELETE FROM ELEVE WHERE ID = :ID");
    query.bindValue(":ID", id);
    return query.exec();
}

bool eleve::modifier() {
    QSqlQuery query;

    query.prepare("UPDATE ELEVE SET NOM=:NOM, PRENOM=:PRENOM, NIVEAU=:NIVEAU, Id_activite=:ID_ACTIVITE WHERE ID=:ID");
    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":NIVEAU", niveauscolaire);
    query.bindValue(":ID_ACTIVITE", id_activite);
    query.bindValue(":ID", id);

    return query.exec();
}

QSqlQueryModel *eleve::recherche(int i, QString s) {
    QSqlQueryModel *model = new QSqlQueryModel();
    switch (i) {
        case 1: model->setQuery("SELECT * FROM ELEVE WHERE NOM LIKE '" + s + "%'");
                break;
        case 2: model->setQuery("SELECT * FROM ELEVE WHERE ID LIKE '" + s + "%'");
                break;
        case 3: model->setQuery("SELECT * FROM ELEVE WHERE NIVEAU LIKE '" + s + "%'");
                break;
    }
    return model;
}

QSqlQueryModel *eleve::sort(int i) {
    QSqlQueryModel *model = new QSqlQueryModel();
    switch (i) {
        case 1: model->setQuery("SELECT * FROM ELEVE ORDER BY NOM");
                break;
        case 2: model->setQuery("SELECT * FROM ELEVE ORDER BY ID");
                break;
        case 3: model->setQuery("SELECT * FROM ELEVE ORDER BY NIVEAU");
                break;
    }
    return model;
}

void eleve::exportpdf(QString s) {
    QString s1 = "C:/Users/essay/Desktop/qt/" + s + ".pdf";
    QPdfWriter pdf(s1);

    QPainter painter(&pdf);

    int i = 4000;
    QImage logoImage("C:/Users/essay/Downloads/garderieeee.jpg");
    if (!logoImage.isNull()) {
        painter.drawImage(QRect(100, 100, 9000, 2000), logoImage); }


    int squareWidth = 4000;
    int squareX = (pdf.width() - squareWidth) / 2;

    painter.setFont(QFont("Century Gothic", 50, QFont::Bold));
    painter.setPen(Qt::blue);


    int titleX = squareX + (squareWidth - painter.fontMetrics().width("LISTE DES ELEVES")) / 2;

    painter.drawText(titleX, 1200, "LISTE DES ELEVES");

    painter.setFont(QFont("Century Gothic", 9));
    painter.setPen(Qt::black);
    painter.drawText(500, 3300, "ID");
    painter.drawText(1500, 3300, "NOM");
    painter.drawText(3500, 3300, "PRENOM");
    painter.drawText(5000, 3300, "NIVEAU");
    painter.drawText(6500, 3300, "Id_activite");

    QSqlQuery query;
    query.prepare("SELECT * FROM ELEVE");
    query.exec();
    while (query.next()) {
        painter.drawText(500, i, query.value(0).toString());
        painter.drawText(1800, i, query.value(1).toString());
        painter.drawText(3500, i, query.value(2).toString());
        painter.drawText(5000, i, query.value(3).toString());
        painter.drawText(6500, i, query.value(4).toString());

        i = i + 500;
    }
}
