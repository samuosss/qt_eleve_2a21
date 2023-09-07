#include "activite.h"

#include "connexion.h"

bool activite::ajouter() {
    QSqlQuery query;

    query.prepare("INSERT INTO activite (id_dac, NOM_dac, type_dac, date_dac) "
                  "VALUES (:ID, :NOM, :PRENOM, :NIVEAU)");
    query.bindValue(":ID", id_ac);
    query.bindValue(":NOM", nom_dac);
    query.bindValue(":PRENOM", type_dac);
    query.bindValue(":NIVEAU", date_dac);

    return query.exec();
}

QSqlQueryModel *activite::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM activite");  // Change table name to "activite"
    return model;
}

bool activite::supprimer(QString id) {
    QSqlQuery query;

    query.prepare("DELETE FROM activite WHERE id_dac = :ID");  // Change table name and attribute
    query.bindValue(":ID", id);
    return query.exec();
}

bool activite::modifier() {
    QSqlQuery query;

    query.prepare("UPDATE activite SET nom_dac=:NOM, type_dac=:TYPE, date_dac=:DATE WHERE id_dac=:ID");  // Change table name and attributes
    query.bindValue(":NOM", nom_dac);
    query.bindValue(":TYPE", type_dac);
    query.bindValue(":DATE", date_dac);

    return query.exec();
}

QSqlQueryModel *activite::recherche(int i, QString s) {
    QSqlQueryModel *model = new QSqlQueryModel();
    switch (i) {
        case 1: model->setQuery("SELECT * FROM activite WHERE nom_dac LIKE '" + s + "%'");  // Change table name and attribute
                break;
        case 2: model->setQuery("SELECT * FROM activite WHERE date_dac LIKE '" + s + "%'");  // Change table name and attribute
                break;
        case 3: model->setQuery("SELECT * FROM activite WHERE id_dac LIKE '" + s + "%'");  // Change table name and attribute
                break;
    }
    return model;
}

QSqlQueryModel *activite::sort(int i) {
    QSqlQueryModel *model = new QSqlQueryModel();
    switch (i) {
        case 1: model->setQuery("SELECT * FROM activite ORDER BY nom_dac");  // Change table name and attribute
                break;
        case 2: model->setQuery("SELECT * FROM activite ORDER BY date_dac");  // Change table name and attribute
                break;
        case 3: model->setQuery("SELECT * FROM activite ORDER BY id_dac");  // Change table name and attribute
                break;
    }
    return model;
}

void activite::exportpdf(QString s) {
    QString s1 = "C:/Users/essay/Desktop/qt/" + s + ".pdf";
    QPdfWriter pdf(s1);

    QPainter painter(&pdf);

    int i = 4000;
    QImage logoImage("C:/Users/essay/Downloads/4_lg.jpg");
    if (!logoImage.isNull()) {
        painter.drawImage(QRect(100, 100, 9000, 2000), logoImage); }

    int squareWidth = 4000;
    int squareX = (pdf.width() - squareWidth) / 2;

    painter.setFont(QFont("Century Gothic", 50, QFont::Bold));
    painter.setPen(Qt::blue);

    int titleX = squareX + (squareWidth - painter.fontMetrics().width("LISTE DES ACTIVITES")) / 2;  // Change title

    painter.drawText(titleX, 1200, "LISTE DES ACTIVITES");  // Change title

    painter.setFont(QFont("Century Gothic", 9));
    painter.setPen(Qt::black);
    painter.drawText(500, 3300, "ID");
    painter.drawText(1500, 3300, "NOM");
    painter.drawText(3500, 3300, "TYPE");
    painter.drawText(8000, 3300, "DATE");

    QSqlQuery query;
    query.prepare("SELECT * FROM activite");  // Change table name
    query.exec();
    while (query.next()) {
        painter.drawText(500, i, query.value(0).toString());
        painter.drawText(1800, i, query.value(1).toString());
        painter.drawText(3500, i, query.value(2).toString());
        painter.drawText(8000, i, query.value(3).toString());

        i = i + 500;
    }
}

