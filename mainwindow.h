#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include  "libplayerc++/playerc++.h"
#include <QTimer>
#include "ui_mainwindow.h"
#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include <QGraphicsScene>
#include <QtGui/QRadioButton>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
    
public:
    // Wykres prędkości, zbliżania się do przeszkody
    QwtPlotCurve *cSpeed; //wskażniik do rysownika
    //wykres orientacji
    QwtPlotCurve *cOrientation;
    QGraphicsScene *scene;//scena dla orientacji


    /////****
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();




   //zmienne klasy okna przechowujące dane na nim wyświetlane
   //****
   double x[100000];
   double y[100000];
   double x1[100000];
   double y1[100000];
   double route;

   int c;
   int d;
   int secCounter;
   double runTime;
   //Metody pomocnicze
   //****
   void SpeedPlotDisplay();
   void PlotDisplay();
   void OrientationView();
   void LcdDisplay();
   void ConnectToPlayer();
   void StartAlgorithm();
   void CheckConn();
   void Time();
   void TimeCounter();
   void LoadPictures();
   void RouteCalculate();
   void CheckMaxTime();

    
private slots:



    void run();
    void run2();



    void on_pushButtonStart_clicked();

    void on_pushButtonStop_clicked();

    void on_pushButtonExit_clicked();

    void on_pushButtonAbout_clicked();

    void on_pushButtonConnect_clicked();

    void on_pushButtonDisconnect_clicked();

   // void on_radioButton_pressed();

    void on_doubleSpinBoxObsDis_valueChanged(const QString &arg1);

    void on_spinBoxDywer_valueChanged(int arg1);

    void on_doubleSpinBoxDywer_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
