#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "test.h"
#include  "libplayerc++/playerc++.h"
#include "math.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QMessageBox>
#include <QImage>
#include <QTextCodec>
#include <QString>
#include <QGraphicsTextItem>

////***
#include "Laser.h"
#include "TS.h"
#include "Sick.h"
#include "Algorithm.h"
///***
PlayerCc::PlayerClient *robot;
PlayerCc::Position2dProxy *p2dProxy;
PlayerCc::LaserProxy *laserProxy;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Sloty

    connect(ui->pushButtonExit, SIGNAL(clicked()), this, SLOT(close()));//About


    //Wykresy
        cSpeed = new QwtPlotCurve;
        cOrientation = new QwtPlotCurve;
    //********Parametry************
        cSpeed->setLegendAttribute(QwtPlotCurve::LegendShowLine, true);
        cSpeed->setPen(QPen(Qt::red));
        cSpeed->attach(ui->speedPlot);
    //**
        cOrientation->setLegendAttribute(QwtPlotCurve::LegendShowSymbol, true);
        cOrientation->setPen(QPen(Qt::blue));
        cOrientation->attach(ui->speedPlot);

    //
         scene = new QGraphicsScene;

         QString filename = "neptun.png";

         QImage image(filename);



         QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
          scene->addItem(item);

          ui->orientationGraphicsView->setScene(scene);
          ui->orientationGraphicsView->show();
    //Funkcje inicjalizujące połaczenie
       // ConnectToPlayer();

    //Timery odświeżające dane na GUI
        QTimer *timer = new QTimer(this);
        QTimer *timer2 = new QTimer(this);
    //***Metody timerowane
        connect(timer, SIGNAL(timeout()), this, SLOT(run()));
        timer->start(100);

        connect(timer2, SIGNAL(timeout()), this, SLOT(run2()));
        timer2->start(1000);

    //Zmienne inicjalizowane w czasie tworzenia okna

        c=0; //zmienna pomocnicza cSpeedPlot
        d=0;
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1250"));

        //inicjalizacja początkowych wartoci

        ui->doubleSpinBoxX->setValue(5);
        ui->doubleSpinBoxY->setValue(5);
        ui->doubleSpinBoxR->setValue(0);
        ui->doubleSpinBoxT->setValue(0.01);
        ui->doubleSpinBoxT->setValue(0.1);
        ui->lineEditConn->setText(QString :: fromUtf8("Rozłączony"));




       }
//*******Zmienne full global;]*********
Test *t;
Algorithm *b;
bool start = false;

//connect to Player & interface set
//PlayerCc::PlayerClient robot("localhost",6665);

//PlayerCc::Position2dProxy p2dProxy(robot,0);
//PlayerCc::LaserProxy laserProxy(robot,0);

// target_point
player_pose2d_t target_point;

//**************************************

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CheckConn(){


   //if(robot->Connected()) {ui->lineEditConn->setText(QString :: fromUtf8("Połączony"));}
   //else {ui->lineEditConn->setText(QString :: fromUtf8("Rozłączony"));}

}



void MainWindow::ConnectToPlayer()
{

    try{

    robot = new PlayerCc::PlayerClient("localhost",6665);
    if(robot->Connected())
    {

        ui->lineEditConn->setText(QString :: fromUtf8("Połączony"));

        p2dProxy = new PlayerCc::Position2dProxy(robot,0);
        laserProxy = new PlayerCc::LaserProxy(robot,0);


    }

       }
    catch(PlayerCc::PlayerError & e)
    {

        QMessageBox::about(this,QString :: fromUtf8("Błąd Połaczenia"),QString::fromStdString(e.GetErrorStr()));

    }
    /*


*/

}
void MainWindow::StartAlgorithm(){


    //enable motors

            p2dProxy->SetMotorEnable(1);
            //request geometries
            p2dProxy->RequestGeom();
            laserProxy->RequestGeom();

            target_point.px = ui->doubleSpinBoxX->value();
            target_point.py = ui->doubleSpinBoxY->value();
            target_point.pa = ui->doubleSpinBoxR->value();


            robot->Read();
           // p2dProxy->SetSpeed(1,0);


           Algorithm *a = new Algorithm;
           a->runAlgo = true;
           start = true;

           a->tolerancy = ui->doubleSpinBoxT->value();
           b = a;
          a->start();



}






void MainWindow::on_pushButton_2_clicked()
{

    //t.start();
    //t.wait();

   ui->lcdNumber->display(b->distanceToTarget);



}

void MainWindow::on_pushButton_3_clicked()
{
    // ui->lcdNumber->display(t.zmienna);
    //cSin->setSamples(x,y,c);
OrientationView();
}
void MainWindow::run()
{
    ui->lcdNumber->display(c);
    c++;
    CheckConn();
    if(start == true){
    if(b->CheckRun()){

     SpeedPlotDisplay();
     OrientationView();
     LcdDisplay();
    }

    ///Sprawdzanie stanu algorytmu
    if(b->CheckRun() == false){ start = false; }
}

}

void MainWindow::run2(){

    if(start == true){
    if(b->CheckRun()){


        PlotDisplay();

    }

}}
//Rysuje wykres prędkości
void MainWindow::SpeedPlotDisplay(){





    if (b->distanceToTarget != 0)
    {

                x[d]= (d/10);
                y[d] =  b->distanceToTarget;


                x1[d] = (d/10);
                y1[d] = 10*(b->GetSpeed());
                d++;
    }


}

//rysuje wykres rysuje sam wykres
void MainWindow::PlotDisplay(){

    cSpeed->setSamples(x,y,d);
    cOrientation->setSamples(x1,y1,d);
    ui->speedPlot->replot();

}

void MainWindow::OrientationView(){






     QMatrix matrix;
     matrix.scale(qreal(0.5), qreal(0.5));
     matrix.rotate(-(b->robotOrientationInDegrees));
     ui->orientationGraphicsView->setMatrix(matrix);

}
void MainWindow::LcdDisplay(){

ui->lcdSpeed->display(b->GetSpeed());
ui->lcdDistance->display(b->distanceToTarget);
ui->lcdOrientation->display(b->robotOrientationInDegrees);

//TODO
//ui->lcdDistanceDo->display();


ui->lcdPositionX->display(b->GetX());
ui->lcdPositionY->display(b->GetY());



}



void MainWindow::on_pushButtonStart_clicked()
{

StartAlgorithm();

}

void MainWindow::on_pushButtonStop_clicked()
{
b->runAlgo = false;

start = false;
b->exit();

sleep(1);
p2dProxy->SetSpeed(0,0);
}

void MainWindow::on_pushButtonExit_clicked()
{

}

void MainWindow::on_pushButtonAbout_clicked()
{

     QMessageBox::about(this,"O programie",QString :: fromUtf8(
     "Praca Magisterska:\n\n Algorytm sterowania robotem mobilnym\n\n\nAutor:\n Michał Dziadosz\n michal.dziadosz@gmail.com\n\nPromotor\n dr. inż. Grzegorz Chwajoł"
                                                               ));

}

void MainWindow::on_pushButtonConnect_clicked()
{

ConnectToPlayer();


}

void MainWindow::on_pushButtonDisconnect_clicked()
{

robot->~PlayerClient();
if(robot->Connected() == false) {ui->lineEditConn->setText(QString :: fromUtf8("disPołączony"));}

}