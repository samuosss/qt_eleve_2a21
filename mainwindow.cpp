#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eleve.h"
#include <QMessageBox>
#include <QSqlQuery>
#include<QMetaObject>
#include<QtEvents>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QFile>
#include <QDataStream>
#include"connexion.h"
#include"qrcode.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{     ui->setupUi(this);

 QDate date=QDate::currentDate();
          QString date1 = "12/12/2023";
          QDate date2 = QDate::fromString(date1,"dd/MM/yyyy");
         ui->date_dac->setDateRange(date,date2);

      ui->tableau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau->setModel(c.afficher());
      ui->tableau_dac->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau_dac->setModel(a.afficher());
      connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
        connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));


          /////////

          QMap<QString, QColor> typeColorMap;
            typeColorMap["Activites artistiques et artisanales"] = QColor(230, 57, 70);
            typeColorMap["Activites physiques et jeux d'exterieur"] = QColor(66,85,86);
            typeColorMap["Activites educatives et de decouverte"] = QColor(180,230,140);
            typeColorMap["Activites de narration et de theatre"] = QColor(255,232,214);
            QSqlQuery query("SELECT type_dac, date_dac FROM activite");

              QCalendarWidget* calendar = ui->calendarWidget;
                while (query.next()) {
                           QString type = query.value(0).toString();
                           QDate date = query.value(1).toDate();

                           if (typeColorMap.contains(type)) {
                               QColor color = typeColorMap.value(type);
                               calendar->setDateTextFormat(date, QTextCharFormat());
                               QTextCharFormat format;
                               format.setBackground(color);
                               calendar->setDateTextFormat(date, format);
                           }
                       }




            //////
            /*
   QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                         QCoreApplication::organizationName(), QCoreApplication::applicationName());

      ui->brow->dynamicCall("Navigate(const QString&)", "https://www.google.com");
*/
      // STATISTIQUE
      QSqlQuery q11, q12, q13, q14, q15;
      int tot1 = 0, c11 = 0, c12 = 0, c13 = 0, c14 = 0;

      q11.prepare("SELECT * FROM activite");
      q11.exec();

        q12.prepare("SELECT * FROM activite WHERE TYPE_DAC='Activites artistiques et artisanales'");
        q12.exec();

        q13.prepare("SELECT * FROM activite WHERE TYPE_DAC='Activites physiques et jeux d''exterieur'");
        q13.exec();

        q14.prepare("SELECT * FROM activite WHERE TYPE_DAC='Activites educatives et de decouverte'");
        q14.exec();

        q15.prepare("SELECT * FROM activite WHERE TYPE_DAC='Activites de narration et de theatre'");
        q15.exec();


      while (q11.next())
      {
          tot1++;
      }
      while (q12.next())
      {
          c11++;
      }
      while (q13.next())
      {
          c12++;
      }
      while (q14.next())
      {
          c13++;
      }
      while (q15.next())
      {
          c14++;
      }

      QBarSet *set11 = new QBarSet("Activites artistiques et artisanales");
      QBarSet *set12 = new QBarSet("Activites physiques et jeux d'exterieur");
      QBarSet *set13 = new QBarSet("Activites educatives et de decouverte");
      QBarSet *set14 = new QBarSet("Activites de narration et de theatre");

      // Add the sets to your QBarSeries and chart as needed

      // Assign values for each bar
      *set11 << c11;
      *set12 << c12;
      *set13 << c13;
      *set14 << c14;

      // Add all sets of data to the chart as a whole
      // 1. Bar Chart
      QBarSeries *series = new QBarSeries();

      // 2. Stacked bar chart
      // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();

      series->append(set11);
      series->append(set12);
      series->append(set13);
      series->append(set14);

      // Used to define the bar chart to display, title
      // legend,
      QChart *chart = new QChart();

      // Add the chart
      chart->addSeries(series);

      // Set title
      chart->setTitle("STATISTIQUE");

      // Define starting animation
      // NoAnimation, GridAxisAnimations, SeriesAnimations
      chart->setAnimationOptions(QChart::AllAnimations);

      // Holds the category titles
      QStringList categories;
      categories << "STATISTIQUE";

      // Adds categories to the axes
      QBarCategoryAxis *axis = new QBarCategoryAxis();
      axis->append(categories);
      chart->createDefaultAxes();

      // 1. Bar chart
      chart->setAxisX(axis, series);

      // 2. Stacked Bar chart

      // Define where the legend is displayed
      chart->legend()->setVisible(true);
      chart->legend()->setAlignment(Qt::AlignBottom);

      // Used to display the chart
      QChartView *chartView = new QChartView(chart);
      chartView->setRenderHint(QPainter::Antialiasing);
      chartView->setMinimumSize(1121, 481);
      chartView->setParent(ui->stat_dac);

      // Used to change the palette
      QPalette pal = qApp->palette();

      // Apply palette changes to the application
      qApp->setPalette(pal);
    // STATISTIQUE
     QSqlQuery q1,q2,q3,q4,q5,q6,q7;
     int tot=0,c1=0,c2=0,c3=0,c4=0,c5=0,c6=0;


     q1.prepare("SELECT * FROM eleve");
     q1.exec();

     q2.prepare("SELECT * FROM eleve WHERE niveau='1er'");
     q2.exec();

     q3.prepare("SELECT * FROM eleve WHERE niveau='2eme'");
     q3.exec();

     q4.prepare("SELECT * FROM eleve WHERE niveau='3eme'");
     q4.exec();

     q5.prepare("SELECT * FROM eleve WHERE niveau='4eme'");
     q5.exec();

     q6.prepare("SELECT * FROM eleve WHERE niveau='5eme'");
     q6.exec();

     q7.prepare("SELECT * FROM eleve WHERE niveau='6eme'");
     q7.exec();




     while (q1.next()){tot++;}
     while (q2.next()){c1++;}
     while (q3.next()){c2++;}
     while (q4.next()){c3++;}
     while (q5.next()){c4++;}
     while (q6.next()){c5++;}
     while (q7.next()){c6++;}
     /*c1=c1/tot;
     c2=c2/tot;
     c3=c3/tot;
     c4=c4/tot;
     c5=c5/tot;*/

    QBarSet *set1 = new QBarSet("1er");
    QBarSet *set2 = new QBarSet("2eme");
    QBarSet *set3 = new QBarSet("3eme");
    QBarSet *set4 = new QBarSet("4eme");
    QBarSet *set5 = new QBarSet("5eme");
    QBarSet *set6 = new QBarSet("6eme");

    // Add the sets to your QBarSeries and chart as needed

    // Assign values for each bar
     *set1 << c1 ;
     *set2 << c2 ;
     *set3 << c3 ;
     *set4 << c4 ;
     *set5 << c5 ;
     *set6 << c6 ;

    // Add all sets of data to the chart as a whole
    // 1. Bar Chart
    QBarSeries *series1 = new QBarSeries();

    // 2. Stacked bar chart
    // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();

    series1->append(set1);
    series1->append(set2);
    series1->append(set3);
    series1->append(set4);
    series1->append(set5);
    series1->append(set6);

    // Used to define the bar chart to display, title
    // legend,
    QChart *chart1 = new QChart();

    // Add the chart
    chart1->addSeries(series1);

    // Set title
    chart1->setTitle("STATISTIQUE");

    // Define starting animation
    // NoAnimation, GridAxisAnimations, SeriesAnimations
    chart1->setAnimationOptions(QChart::AllAnimations);

    // Holds the category titles
    QStringList categories1;
    categories1 << "STATISTIQUE";

    // Adds categories to the axes
    QBarCategoryAxis *axis1 = new QBarCategoryAxis();
    axis1->append(categories);
    chart1->createDefaultAxes();

    // 1. Bar chart
    chart1->setAxisX(axis1, series1);

    // 2. Stacked Bar chart

    // Define where the legend is displayed
    chart1->legend()->setVisible(true);
    chart1->legend()->setAlignment(Qt::AlignBottom);


    // Used to display the chart
    QChartView *chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);
    chartView1->setMinimumSize(1121,481);
    chartView1->setParent(ui->stat);


    // Used to change the palette
    QPalette pal1 = qApp->palette();



    // Apply palette changes to the application
    qApp->setPalette(pal1);



}

MainWindow::~MainWindow()
{
    delete ui;
}

bool containsDigits(const QString& str) {
    for (QChar c : str) {
        if (c.isDigit()) {
            return true;
        }
    }
    return false;
}


void MainWindow::on_ajouter_clicked()
{


QString nom=ui->nom->text();
QString prenom=ui->prenom->text();
QString niveau=ui->niveau->currentText();
QString id=ui->id->text();
QString act=ui->act->text();


eleve C(id,nom,prenom,niveau,act);

bool test=C.ajouter();
if(test){
    if (!containsDigits(nom)&&!containsDigits(prenom)) {

    ui->tableau->setModel(c.afficher());

    QMessageBox::information(nullptr, QObject::tr(" OK"),
                QObject::tr("Ajout Effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    // STATISTIQUE
     QSqlQuery q1,q2,q3,q4,q5,q6,q7;
     int tot=0,c1=0,c2=0,c3=0,c4=0,c5=0,c6=0;


     q1.prepare("SELECT * FROM eleve");
     q1.exec();

     q2.prepare("SELECT * FROM eleve WHERE niveau='1er'");
     q2.exec();

     q3.prepare("SELECT * FROM eleve WHERE niveau='2eme'");
     q3.exec();

     q4.prepare("SELECT * FROM eleve WHERE niveau='3eme'");
     q4.exec();

     q5.prepare("SELECT * FROM eleve WHERE niveau='4eme'");
     q5.exec();

     q6.prepare("SELECT * FROM eleve WHERE niveau='5eme'");
     q6.exec();

     q7.prepare("SELECT * FROM eleve WHERE niveau='6eme'");
     q7.exec();




     while (q1.next()){tot++;}
     while (q2.next()){c1++;}
     while (q3.next()){c2++;}
     while (q4.next()){c3++;}
     while (q5.next()){c4++;}
     while (q6.next()){c5++;}
     while (q7.next()){c6++;}
     /*c1=c1/tot;
     c2=c2/tot;
     c3=c3/tot;
     c4=c4/tot;
     c5=c5/tot;*/

    QBarSet *set1 = new QBarSet("1er");
    QBarSet *set2 = new QBarSet("2eme");
    QBarSet *set3 = new QBarSet("3eme");
    QBarSet *set4 = new QBarSet("4eme");
    QBarSet *set5 = new QBarSet("5eme");
    QBarSet *set6 = new QBarSet("6eme");

    // Add the sets to your QBarSeries and chart as needed

    // Assign values for each bar
     *set1 << c1 ;
     *set2 << c2 ;
     *set3 << c3 ;
     *set4 << c4 ;
     *set5 << c5 ;
     *set6 << c6 ;

    // Add all sets of data to the chart as a whole
    // 1. Bar Chart
    QBarSeries *series = new QBarSeries();

    // 2. Stacked bar chart
    // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();

    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    series->append(set5);
    series->append(set6);

    // Used to define the bar chart to display, title
    // legend,
    QChart *chart = new QChart();

    // Add the chart
    chart->addSeries(series);

    // Set title
    chart->setTitle("STATISTIQUE");

    // Define starting animation
    // NoAnimation, GridAxisAnimations, SeriesAnimations
    chart->setAnimationOptions(QChart::AllAnimations);

    // Holds the category titles
    QStringList categories;
    categories << "STATISTIQUE";

    // Adds categories to the axes
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();

    // 1. Bar chart
    chart->setAxisX(axis, series);

    // 2. Stacked Bar chart

    // Define where the legend is displayed
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);


    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(1121,481);
    chartView->setParent(ui->stat);


    // Used to change the palette
    QPalette pal = qApp->palette();



    // Apply palette changes to the application
    qApp->setPalette(pal);



}
else
    QMessageBox::critical(nullptr, QObject::tr(" OK"),
                QObject::tr("Ajout Non Effectué:Nom ou Prenom d'élève contient des chiffres\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
else
    QMessageBox::critical(nullptr, QObject::tr(" OK"),
                QObject::tr("Ajout Non Effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}





void MainWindow::on_supprimer_clicked()
{       QString id=ui->id->text();
        if(!id.isEmpty()){
bool test=c.supprimer(id);
if(test){
    ui->tableau->setModel(c.afficher());
    QMessageBox::information(nullptr, QObject::tr(" OK"),
                QObject::tr("Suppression Effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    // STATISTIQUE
     QSqlQuery q1,q2,q3,q4,q5,q6,q7;
     int tot=0,c1=0,c2=0,c3=0,c4=0,c5=0,c6=0;


     q1.prepare("SELECT * FROM eleve");
     q1.exec();

     q2.prepare("SELECT * FROM eleve WHERE niveau='1er'");
     q2.exec();

     q3.prepare("SELECT * FROM eleve WHERE niveau='2eme'");
     q3.exec();

     q4.prepare("SELECT * FROM eleve WHERE niveau='3eme'");
     q4.exec();

     q5.prepare("SELECT * FROM eleve WHERE niveau='4eme'");
     q5.exec();

     q6.prepare("SELECT * FROM eleve WHERE niveau='5eme'");
     q6.exec();

     q7.prepare("SELECT * FROM eleve WHERE niveau='6eme'");
     q7.exec();




     while (q1.next()){tot++;}
     while (q2.next()){c1++;}
     while (q3.next()){c2++;}
     while (q4.next()){c3++;}
     while (q5.next()){c4++;}
     while (q6.next()){c5++;}
     while (q7.next()){c6++;}
     /*c1=c1/tot;
     c2=c2/tot;
     c3=c3/tot;
     c4=c4/tot;
     c5=c5/tot;*/

    QBarSet *set1 = new QBarSet("1er");
    QBarSet *set2 = new QBarSet("2eme");
    QBarSet *set3 = new QBarSet("3eme");
    QBarSet *set4 = new QBarSet("4eme");
    QBarSet *set5 = new QBarSet("5eme");
    QBarSet *set6 = new QBarSet("6eme");

    // Add the sets to your QBarSeries and chart as needed

    // Assign values for each bar
     *set1 << c1 ;
     *set2 << c2 ;
     *set3 << c3 ;
     *set4 << c4 ;
     *set5 << c5 ;
     *set6 << c6 ;

    // Add all sets of data to the chart as a whole
    // 1. Bar Chart
    QBarSeries *series = new QBarSeries();

    // 2. Stacked bar chart
    // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();

    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    series->append(set5);
    series->append(set6);

    // Used to define the bar chart to display, title
    // legend,
    QChart *chart = new QChart();

    // Add the chart
    chart->addSeries(series);

    // Set title
    chart->setTitle("STATISTIQUE");

    // Define starting animation
    // NoAnimation, GridAxisAnimations, SeriesAnimations
    chart->setAnimationOptions(QChart::AllAnimations);

    // Holds the category titles
    QStringList categories;
    categories << "STATISTIQUE";

    // Adds categories to the axes
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();

    // 1. Bar chart
    chart->setAxisX(axis, series);

    // 2. Stacked Bar chart

    // Define where the legend is displayed
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);


    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(1121,481);
    chartView->setParent(ui->stat);


    // Used to change the palette
    QPalette pal = qApp->palette();



    // Apply palette changes to the application
    qApp->setPalette(pal);




}
else
    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Suppression Non Effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);}

}

void MainWindow::on_tableau_activated(const QModelIndex &index)
{
    QString id=ui->tableau->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from eleve where ID='"+id+"'");
QString text;
    if(query.exec()){
        while(query.next())
        {
            ui->id->setText(query.value(2).toString());
            ui->prenom-> setText(query.value(1).toString());
            ui->nom->setText(query.value(0).toString());
            ui->niveau->setCurrentText(query.value(3).toString());
            ui->act->setText(query.value(4).toString());



        }

    }

}

void MainWindow::on_modifier_clicked()
{QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString niveau=ui->niveau->currentText();
    QString id=ui->id->text();
    QString act=ui->act->text();
    eleve C(id,nom,prenom,niveau,act);
    if(nom.length()<11&&prenom.length()<21&&id.length()<20){
    if(!nom.isEmpty()&&!id.isEmpty()&&!prenom.isEmpty()){



bool test=C.modifier();
if(test){
    if (!containsDigits(nom)&&!containsDigits(prenom)) {

    ui->tableau->setModel(c.afficher());

    QMessageBox::information(nullptr, QObject::tr(" OK"),
                QObject::tr("Ajout Effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

    // STATISTIQUE
     QSqlQuery q1,q2,q3,q4,q5,q6,q7;
     int tot=0,c1=0,c2=0,c3=0,c4=0,c5=0,c6=0;


     q1.prepare("SELECT * FROM eleve");
     q1.exec();

     q2.prepare("SELECT * FROM eleve WHERE niveau='1er'");
     q2.exec();

     q3.prepare("SELECT * FROM eleve WHERE niveau='2eme'");
     q3.exec();

     q4.prepare("SELECT * FROM eleve WHERE niveau='3eme'");
     q4.exec();

     q5.prepare("SELECT * FROM eleve WHERE niveau='4eme'");
     q5.exec();

     q6.prepare("SELECT * FROM eleve WHERE niveau='5eme'");
     q6.exec();

     q7.prepare("SELECT * FROM eleve WHERE niveau='6eme'");
     q7.exec();




     while (q1.next()){tot++;}
     while (q2.next()){c1++;}
     while (q3.next()){c2++;}
     while (q4.next()){c3++;}
     while (q5.next()){c4++;}
     while (q6.next()){c5++;}
     while (q7.next()){c6++;}
     /*c1=c1/tot;
     c2=c2/tot;
     c3=c3/tot;
     c4=c4/tot;
     c5=c5/tot;*/

    QBarSet *set1 = new QBarSet("1er");
    QBarSet *set2 = new QBarSet("2eme");
    QBarSet *set3 = new QBarSet("3eme");
    QBarSet *set4 = new QBarSet("4eme");
    QBarSet *set5 = new QBarSet("5eme");
    QBarSet *set6 = new QBarSet("6eme");

    // Add the sets to your QBarSeries and chart as needed

    // Assign values for each bar
     *set1 << c1 ;
     *set2 << c2 ;
     *set3 << c3 ;
     *set4 << c4 ;
     *set5 << c5 ;
     *set6 << c6 ;

    // Add all sets of data to the chart as a whole
    // 1. Bar Chart
    QBarSeries *series = new QBarSeries();

    // 2. Stacked bar chart
    // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();

    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    series->append(set5);
    series->append(set6);

    // Used to define the bar chart to display, title
    // legend,
    QChart *chart = new QChart();

    // Add the chart
    chart->addSeries(series);

    // Set title
    chart->setTitle("STATISTIQUE");

    // Define starting animation
    // NoAnimation, GridAxisAnimations, SeriesAnimations
    chart->setAnimationOptions(QChart::AllAnimations);

    // Holds the category titles
    QStringList categories;
    categories << "STATISTIQUE";

    // Adds categories to the axes
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();

    // 1. Bar chart
    chart->setAxisX(axis, series);

    // 2. Stacked Bar chart

    // Define where the legend is displayed
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);


    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(1121,481);
    chartView->setParent(ui->stat);


    // Used to change the palette
    QPalette pal = qApp->palette();



    // Apply palette changes to the application
    qApp->setPalette(pal);



}
    else
        QMessageBox::critical(nullptr, QObject::tr(" OK"),
                    QObject::tr("Ajout Non Effectué:Nom ou Prenom d'élève contient des chiffres\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
else
    QMessageBox::critical(nullptr, QObject::tr(" OK"),
                QObject::tr("Ajout Non Effectué: L'ID n'existe pas.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}
else
    QMessageBox::critical(nullptr, QObject::tr(" OK"),
                QObject::tr("Ajout Non Effectué : Un ou plusieurs cases sont vide .\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);




}
else QMessageBox::critical(nullptr, QObject::tr(" OK"),
                            QObject::tr("Ajout Non Effectué: Vous avez écrit plus que le maximum d'une case.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);



 }





void MainWindow::on_pb_recher_clicked()
{
    QString s=ui->rechercher->text();

    if(ui->rech->currentText()=="Nom d'élève")
       ui->tableau->setModel(c.recherche(1,s));
    if(ui->rech->currentText()=="ID d'élève")
       ui->tableau->setModel( c.recherche(2,s));
    if(ui->rech->currentText()=="Niveau d'élève")
        ui->tableau->setModel(c.recherche(3,s));
}

void MainWindow::on_pb_tri_clicked()
{
    if(ui->tri->currentText()=="Nom d'élève")
       ui->tableau->setModel(c.sort(1));
    if(ui->tri->currentText()=="ID d'élève")
       ui->tableau->setModel( c.sort(2));
    if(ui->tri->currentText()=="Niveau d'élève")
        ui->tableau->setModel(c.sort(3));
}

void MainWindow::on_pb_pdf_clicked()
{   QString s;
    s=ui->PDF->text();
    c.exportpdf(s);
}

void MainWindow::on_pb_camera_clicked()
{
    ca= new camera();
    ca->show();
}

void MainWindow::on_ajouter_dac_clicked()
{

    QString nom_dac = ui->nom_dac->text();
    QString id_dac = ui->id_dac->text();
    QString type_dac = ui->type_dac->currentText();
    QDate date_dac = ui->date_dac->date();
    activite A(id_dac, nom_dac, type_dac, date_dac);

    bool test = A.ajouter();
    if (test)
    { /////////

        QMap<QString, QColor> typeColorMap;
        typeColorMap["Activites artistiques et artisanales"] = QColor(230, 57, 70);
        typeColorMap["Activites physiques et jeux d'exterieur"] = QColor(66,85,86);
        typeColorMap["Activites educatives et de decouverte"] = QColor(241,250,238);
        typeColorMap["Activites de narration et de theatre"] = QColor(255,232,214);  QSqlQuery query("SELECT type_dac, date_dac FROM activite");

            QCalendarWidget* calendar = ui->calendarWidget;
              while (query.next()) {
                         QString type = query.value(0).toString();
                         QDate date = query.value(1).toDate();

                         if (typeColorMap.contains(type)) {
                             QColor color = typeColorMap.value(type);
                             calendar->setDateTextFormat(date, QTextCharFormat());
                             QTextCharFormat format;
                             format.setBackground(color);
                             calendar->setDateTextFormat(date, format);
                         }
                     }




          //////
        ui->tableau_dac->setModel(A.afficher());
        // STATISTIQUE
        QSqlQuery q1, q2, q3, q4, q5;
        int tot = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0;

        q1.prepare("SELECT * FROM activite");
        q1.exec();

        q2.prepare("SELECT * FROM activite WHERE type_dac='Activites artistiques et artisanales'");
        q2.exec();

        q3.prepare("SELECT * FROM activite WHERE type_dac='Activites physiques et jeux d''exterieur'");
        q3.exec();

        q4.prepare("SELECT * FROM activite WHERE type_dac='Activites educatives et de decouverte'");
        q4.exec();

        q5.prepare("SELECT * FROM activite WHERE type_dac='Activites de narration et de theatre'");
        q5.exec();

        while (q1.next())
        {
            tot++;
        }
        while (q2.next())
        {
            c1++;
        }
        while (q3.next())
        {
            c2++;
        }
        while (q4.next())
        {
            c3++;
        }
        while (q5.next())
        {
            c4++;
        }

        QBarSet *set1 = new QBarSet("Activites artistiques et artisanales");
        QBarSet *set2 = new QBarSet("Activites physiques et jeux d'exterieur");
        QBarSet *set3 = new QBarSet("Activites educatives et de decouverte");
        QBarSet *set4 = new QBarSet("Activites de narration et de theatre");

        // Add the sets to your QBarSeries and chart as needed

        // Assign values for each bar
        *set1 << c1;
        *set2 << c2;
        *set3 << c3;
        *set4 << c4;

        // Add all sets of data to the chart as a whole
        // 1. Bar Chart
        QBarSeries *series = new QBarSeries();

        // 2. Stacked bar chart
        // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();

        series->append(set1);
        series->append(set2);
        series->append(set3);
        series->append(set4);

        // Used to define the bar chart to display, title
        // legend,
        QChart *chart = new QChart();

        // Add the chart
        chart->addSeries(series);

        // Set title
        chart->setTitle("STATISTIQUE");

        // Define starting animation
        // NoAnimation, GridAxisAnimations, SeriesAnimations
        chart->setAnimationOptions(QChart::AllAnimations);

        // Holds the category titles
        QStringList categories;
        categories << "STATISTIQUE";

        // Adds categories to the axes
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categories);
        chart->createDefaultAxes();

        // 1. Bar chart
        chart->setAxisX(axis, series);

        // 2. Stacked Bar chart

        // Define where the legend is displayed
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        // Used to display the chart
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setMinimumSize(1121, 481);
        chartView->setParent(ui->stat_dac);

        // Used to change the palette
        QPalette pal = qApp->palette();

        // Apply palette changes to the application
        qApp->setPalette(pal);
        QMessageBox::information(nullptr, QObject::tr(" OK"),
                                 QObject::tr("Ajout Effectué.\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);
    }

    else
        QMessageBox::critical(nullptr, QObject::tr(" OK"),
                              QObject::tr("Ajout Non Effectué\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
}

void MainWindow::on_supprimer_dac_clicked()
{
    QString id = ui->id_dac->text();
    if (!id.isEmpty())
    {
        bool test = a.supprimer(id);
        if (test)
        { /////////

            QMap<QString, QColor> typeColorMap;
            typeColorMap["Activites artistiques et artisanales"] = QColor(230, 57, 70);
            typeColorMap["Activites physiques et jeux d'exterieur"] = QColor(66,85,86);
            typeColorMap["Activites educatives et de decouverte"] = QColor(241,250,238);
            typeColorMap["Activites de narration et de theatre"] = QColor(255,232,214);
              QSqlQuery query("SELECT type_dac, date_dac FROM activite");

                QCalendarWidget* calendar = ui->calendarWidget;
                  while (query.next()) {
                             QString type = query.value(0).toString();
                             QDate date = query.value(1).toDate();

                             if (typeColorMap.contains(type)) {
                                 QColor color = typeColorMap.value(type);
                                 calendar->setDateTextFormat(date, QTextCharFormat());
                                 QTextCharFormat format;
                                 format.setBackground(color);
                                 calendar->setDateTextFormat(date, format);
                             }
                         }




              //////
            ui->tableau_dac->setModel(a.afficher());
            // STATISTIQUE
            QSqlQuery q1, q2, q3, q4, q5;
            int tot = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0;

            q1.prepare("SELECT * FROM activite");
            q1.exec();

            q2.prepare("SELECT * FROM activite WHERE type_dac='Activites artistiques et artisanales'");
            q2.exec();

            q3.prepare("SELECT * FROM activite WHERE type_dac='Activites physiques et jeux d''exterieur'");
            q3.exec();

            q4.prepare("SELECT * FROM activite WHERE type_dac='Activites educatives et de decouverte'");
            q4.exec();

            q5.prepare("SELECT * FROM activite WHERE type_dac='Activites de narration et de theatre'");
            q5.exec();

            while (q1.next())
            {
                tot++;
            }
            while (q2.next())
            {
                c1++;
            }
            while (q3.next())
            {
                c2++;
            }
            while (q4.next())
            {
                c3++;
            }
            while (q5.next())
            {
                c4++;
            }

            QBarSet *set1 = new QBarSet("Activites artistiques et artisanales");
            QBarSet *set2 = new QBarSet("Activites physiques et jeux d'exterieur");
            QBarSet *set3 = new QBarSet("Activites educatives et de decouverte");
            QBarSet *set4 = new QBarSet("Activites de narration et de theatre");

            // Add the sets to your QBarSeries and chart as needed

            // Assign values for each bar
            *set1 << c1;
            *set2 << c2;
            *set3 << c3;
            *set4 << c4;

            // Add all sets of data to the chart as a whole
            // 1. Bar Chart
            QBarSeries *series = new QBarSeries();

            // 2. Stacked bar chart
            // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();

            series->append(set1);
            series->append(set2);
            series->append(set3);
            series->append(set4);

            // Used to define the bar chart to display, title
            // legend,
            QChart *chart = new QChart();

            // Add the chart
            chart->addSeries(series);

            // Set title
            chart->setTitle("STATISTIQUE");

            // Define starting animation
            // NoAnimation, GridAxisAnimations, SeriesAnimations
            chart->setAnimationOptions(QChart::AllAnimations);

            // Holds the category titles
            QStringList categories;
            categories << "STATISTIQUE";

            // Adds categories to the axes
            QBarCategoryAxis *axis = new QBarCategoryAxis();
            axis->append(categories);
            chart->createDefaultAxes();

            // 1. Bar chart
            chart->setAxisX(axis, series);

            // 2. Stacked Bar chart

            // Define where the legend is displayed
            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignBottom);

            // Used to display the chart
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->setMinimumSize(1121, 481);
            chartView->setParent(ui->stat_dac);

            // Used to change the palette
            QPalette pal = qApp->palette();

            // Apply palette changes to the application
            qApp->setPalette(pal);
            QMessageBox::information(nullptr, QObject::tr(" OK"),
                                     QObject::tr("Suppression Effectué.\n"
                                                 "Click Cancel to exit."),
                                     QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Suppression Non Effectué.\n"
                                              "Click Cancel to exit."),
                                  QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Suppression Non Effectué : La case de suppression est vide.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
}

void MainWindow::on_tableau_dac_activated(const QModelIndex &index)
{
    QString id = ui->tableau_dac->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from activite where id_dac='" + id + "'");
    QString text;
    if (query.exec())
    {
        while (query.next())
        {
            ui->id_dac->setText(query.value(0).toString());
            ui->nom_dac->setText(query.value(1).toString());
            ui->type_dac->setCurrentText(query.value(2).toString());
            ui->date_dac->setDate(query.value(3).toDate());
            text="detail d'activitè :"+query.value(0).toString()+"\n"+query.value(1).toString()+"\n"+query.value(2).toString()+"\n"+query.value(3).toString()+"\n";

        }
        using namespace qrcodegen;
                   // Create the QR Code object
                   QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
                   qint32 sz = qr.getSize();
                   QImage im(sz,sz, QImage::Format_RGB32);
                     QRgb black = qRgb(  0,  0,  0);
                     QRgb white = qRgb(255,255,255);
                   for (int y = 0; y < sz; y++)
                     for (int x = 0; x < sz; x++)
                       im.setPixel(x,y,qr.getModule(x, y) ? black : white );
                   ui->qrcode_2->setPixmap( QPixmap::fromImage(im.scaled(150,150,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );

    }
}

void MainWindow::on_modifier_dac_clicked()
{
    QString nom_dac = ui->nom_dac->text();
    QString id_dac = ui->id_dac->text();
    QString type_dac = ui->type_dac->currentText();
    QDate date_dac = ui->date_dac->date();
    activite A(id_dac, nom_dac, type_dac, date_dac);



            bool test = a.modifier();
            if (test)
            {

                /////////

                QMap<QString, QColor> typeColorMap;
                typeColorMap["Activites artistiques et artisanales"] = QColor(230, 57, 70);
                typeColorMap["Activites physiques et jeux d'exterieur"] = QColor(66,85,86);
                typeColorMap["Activites educatives et de decouverte"] = QColor(241,250,238);
                typeColorMap["Activites de narration et de theatre"] = QColor(255,232,214);
                  QSqlQuery query("SELECT type_dac, date_dac FROM activite");

                    QCalendarWidget* calendar = ui->calendarWidget;
                      while (query.next()) {
                                 QString type = query.value(0).toString();
                                 QDate date = query.value(1).toDate();

                                 if (typeColorMap.contains(type)) {
                                     QColor color = typeColorMap.value(type);
                                     calendar->setDateTextFormat(date, QTextCharFormat());
                                     QTextCharFormat format;
                                     format.setBackground(color);
                                     calendar->setDateTextFormat(date, format);
                                 }
                             }




                  //////
                ui->tableau_dac->setModel(A.afficher());
                // STATISTIQUE
                QSqlQuery q1, q2, q3, q4, q5;
                int tot = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0;

                q1.prepare("SELECT * FROM activite");
                q1.exec();

                q2.prepare("SELECT * FROM activite WHERE type_dac='Activites artistiques et artisanales'");
                q2.exec();

                q3.prepare("SELECT * FROM activite WHERE type_dac='Activites physiques et jeux d''exterieur'");
                q3.exec();

                q4.prepare("SELECT * FROM activite WHERE type_dac='Activites educatives et de decouverte'");
                q4.exec();

                q5.prepare("SELECT * FROM activite WHERE type_dac='Activites de narration et de theatre'");
                q5.exec();

                while (q1.next())
                {
                    tot++;
                }
                while (q2.next())
                {
                    c1++;
                }
                while (q3.next())
                {
                    c2++;
                }
                while (q4.next())
                {
                    c3++;
                }
                while (q5.next())
                {
                    c4++;
                }

                QBarSet *set1 = new QBarSet("Activites artistiques et artisanales");
                QBarSet *set2 = new QBarSet("Activites physiques et jeux d'exterieur");
                QBarSet *set3 = new QBarSet("Activites educatives et de decouverte");
                QBarSet *set4 = new QBarSet("Activites de narration et de theatre");

                // Add the sets to your QBarSeries and chart as needed

                // Assign values for each bar
                *set1 << c1;
                *set2 << c2;
                *set3 << c3;
                *set4 << c4;

                // Add all sets of data to the chart as a whole
                // 1. Bar Chart
                QBarSeries *series = new QBarSeries();

                // 2. Stacked bar chart
                // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();

                series->append(set1);
                series->append(set2);
                series->append(set3);
                series->append(set4);

                // Used to define the bar chart to display, title
                // legend,
                QChart *chart = new QChart();

                // Add the chart
                chart->addSeries(series);

                // Set title
                chart->setTitle("STATISTIQUE");

                // Define starting animation
                // NoAnimation, GridAxisAnimations, SeriesAnimations
                chart->setAnimationOptions(QChart::AllAnimations);

                // Holds the category titles
                QStringList categories;
                categories << "STATISTIQUE";

                // Adds categories to the axes
                QBarCategoryAxis *axis = new QBarCategoryAxis();
                axis->append(categories);
                chart->createDefaultAxes();

                // 1. Bar chart
                chart->setAxisX(axis, series);

                // 2. Stacked Bar chart

                // Define where the legend is displayed
                chart->legend()->setVisible(true);
                chart->legend()->setAlignment(Qt::AlignBottom);

                // Used to display the chart
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                chartView->setMinimumSize(1121, 481);
                chartView->setParent(ui->stat_dac);

                // Used to change the palette
                QPalette pal = qApp->palette();

                // Apply palette changes to the application
                qApp->setPalette(pal);
                QMessageBox::information(nullptr, QObject::tr(" OK"),
                                         QObject::tr("Ajout Effectué.\n"
                                                     "Click Cancel to exit."),
                                         QMessageBox::Cancel);
            }
            else
                QMessageBox::critical(nullptr, QObject::tr(" OK"),
                                      QObject::tr("Modification Non Effectué\n"
                                                  "Click Cancel to exit."),
                                      QMessageBox::Cancel);

}
void MainWindow::on_pb_recher_dac_clicked()
{
    QString s = ui->rechercher_dac->text();

    if (ui->rech_dac->currentText() == "Nom d'activité")
        ui->tableau_dac->setModel(a.recherche(1, s));
    if (ui->rech_dac->currentText() == "Date d'activité")
        ui->tableau_dac->setModel(a.recherche(2, s));
    if (ui->rech_dac->currentText() == "ID d'activité")
        ui->tableau_dac->setModel(a.recherche(3, s));
}

void MainWindow::on_pb_tri_dac_clicked()
{
    if (ui->tri_dac->currentText() == "Nom d'activité")
        ui->tableau_dac->setModel(a.sort(1));
    if (ui->tri_dac->currentText() == "Date d'activité")
        ui->tableau_dac->setModel(a.sort(2));
    if (ui->tri_dac->currentText() == "ID d'activité")
        ui->tableau_dac->setModel(a.sort(3));
}

void MainWindow::on_pb_pdf_dac_clicked()
{
    QString s;
    s = ui->PDF_dac->text();
    a.exportpdf(s);
}


void MainWindow::sendMail()
{//associé a un bouton grace a une fonction predefine par smtp.cpp
    Smtp* smtp = new Smtp("essayehmalek@gmail.com","cfcnjmgydkbstsgk","smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));



    smtp->sendMail("essayehmalek@gmail.com", ui->mail->text() , "absence","Monsieur/Madame "+ui->np->text()+" "+ui->pp->text()+" nous vous informe que votre enfant était absent aujourd'hui\n Cordialement");
}


