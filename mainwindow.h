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

   int c;
   int d;
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
    
private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void run();
    void run2();



    void on_pushButtonStart_clicked();

    void on_pushButtonStop_clicked();

    void on_pushButtonExit_clicked();

    void on_pushButtonAbout_clicked();

    void on_pushButtonConnect_clicked();

    void on_pushButtonDisconnect_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
