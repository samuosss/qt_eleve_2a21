#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"eleve.h"
#include"camera.h"
#include"activite.h"
#include"smtp.h"
#include<QtCharts>
#include<QChartView>
#include<QLineSeries>
#include <QCloseEvent>
#include <QString>
#include <QUrl>
#include <QKeySequenceEdit>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_clicked();
    void on_supprimer_clicked();
    void on_tableau_activated(const QModelIndex &index);
    void on_modifier_clicked();

    void on_pb_recher_clicked();

    void on_pb_tri_clicked();

    void on_pb_pdf_clicked();
    void on_ajouter_dac_clicked();
    void on_supprimer_dac_clicked();
    void on_tableau_dac_activated(const QModelIndex &index);
    void on_modifier_dac_clicked();

    void on_pb_recher_dac_clicked();

    void on_pb_tri_dac_clicked();

    void on_pb_pdf_dac_clicked();
    void on_pb_camera_clicked();
      void sendMail();



private:
    Ui::MainWindow *ui;
    eleve c;
    QFile sourceFile;
    camera *ca;
    QStringList files;
    activite a;

};
#endif // MAINWINDOW_H
