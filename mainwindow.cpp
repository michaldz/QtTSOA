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
#include <QDateTime>

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
         LoadPictures();



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
        route = 0;
        runTime = 0;
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1250"));

        //inicjalizacja początkowych wartoci

        ui->doubleSpinBoxX->setValue(5);
        ui->doubleSpinBoxY->setValue(5);
        ui->doubleSpinBoxR->setValue(0);
        ui->doubleSpinBoxT->setValue(0.01);
        ui->doubleSpinBoxT->setValue(0.1);
        ui->lineEditConn->setText(QString :: fromUtf8("Rozłączony"));
        ui->lineEditHost->setText("localhost");
        ui->spinBoxPort->setValue(6665);
        ui->pushButtonDisconnect->setDisabled(true);
        ui->pushButtonStop->setDisabled(true);
        ui->pushButtonStart->setDisabled(true);
        ui->doubleSpinBoxObsDis->setValue(0.1);
        ui->spinBoxDywer->setValue(5);
        ui->doubleSpinBoxDywer->setValue(1.5);






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

void MainWindow::LoadPictures(){






     try
     {

     QString filename = "neptun.png";

     QImage image(filename);
     QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
     scene->addItem(item);
      }
     catch(...)
     {
        QMessageBox::about(this,QString :: fromUtf8("Błąd pliku"),QString::fromStdString("Błąd pliku"));

     }



     ui->orientationGraphicsView->setScene(scene);
     ui->orientationGraphicsView->show();

}

void MainWindow::Time()
{




            QDate date = QDate::currentDate();
            QString dateString = date.toString();



            QTime time = QTime::currentTime();
            QString timeString = time.toString();

            ui->statusBar->showMessage(dateString + " " + timeString + ", " + "Gotowy do Pracy");


}
void MainWindow::TimeCounter()
{

    QString timeSec, timeMin, timeHou;
   //QString roz = "Rozłączony";


    if(ui->lineEditConn->text()  != QString :: fromUtf8("Połączony"))
    {
     secCounter = 0;
    }
    else
    {
     secCounter++;
    }
    if(secCounter<60){
    timeSec.setNum(secCounter);

    ui->labelTime->setText(timeSec + "s");
        }
    else if(secCounter < 3600)
    {
        timeMin.setNum(secCounter/60);
        timeSec.setNum(secCounter%60);

        ui->labelTime->setText(timeMin + "m" + " " + timeSec + "s");

    }
    else
    {
        timeHou.setNum(secCounter/3600);
        timeMin.setNum(secCounter%3600/60);
        timeSec.setNum((secCounter%3600/60)%60);

        ui->labelTime->setText(timeHou + "h" + " " + timeMin + "m" + " " + timeSec + "s");


    }




}

void MainWindow::CheckConn(){


   //if(robot->Connected()) {ui->lineEditConn->setText(QString :: fromUtf8("Połączony"));}
   //else {ui->lineEditConn->setText(QString :: fromUtf8("Rozłączony"));}

}



void MainWindow::ConnectToPlayer()
{

    try{

    robot = new PlayerCc::PlayerClient(ui->lineEditHost->text().toStdString(),ui->spinBoxPort->value());
    if(robot->Connected())
    {

        ui->lineEditConn->setText(QString :: fromUtf8("Połączony"));
        ui->pushButtonDisconnect->setDisabled(false);
        ui->pushButtonConnect->setDisabled(true);
        ui->pushButtonStart->setDisabled(false);

        p2dProxy = new PlayerCc::Position2dProxy(robot,0);
        laserProxy = new PlayerCc::LaserProxy(robot,0);
        route = 0;
        runTime = 0;


    }

       }
    catch(PlayerCc::PlayerError & e)
    {

        QMessageBox::about(this,QString :: fromUtf8("Błąd"),QString::fromStdString(e.GetErrorStr()));


    }
    /*


*/

}
void MainWindow::StartAlgorithm(){



    ui->pushButtonStop->setDisabled(false);
    ui->pushButtonStart->setDisabled(true);
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
           a->SetTabuListSize(ui->spinBoxTabuList->value());
           a->SetAcceptObstacleDistance(ui->doubleSpinBoxObsDis->value());
           a->DywerInit(ui->radioButtonDywer->isChecked(),ui->spinBoxDywer->value(),ui->doubleSpinBoxDywer->value());

           if (ui->radioButtonAspiration->isChecked()){ a->SetAspiration(true); }
           else {a->SetAspiration(false); }

           b = a;
           a->start();



}
void MainWindow::RouteCalculate(){


route = route + 0.1 * b->GetSpeed();
ui->lcdDistanceDo->display(route);

}

void MainWindow::CheckMaxTime(){

    if(ui->radioButtonMaxTime->isChecked() && runTime > ui->spinBoxMaxTime->value()){

        runTime = 0;
        on_pushButtonStop_clicked();

    }



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
     RouteCalculate();
    }

    ///Sprawdzanie stanu algorytmu
    if(b->CheckRun() == false){
        if(b->onTarget == true) { LcdDisplay();
        ui->pushButtonStart->setDisabled(false);
        }
        start = false;


    }
}



}

void MainWindow::run2(){

    Time();
    TimeCounter();


    if(start == true){
    if(b->CheckRun()){

        CheckMaxTime();
        PlotDisplay();
        runTime++;

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
LcdDisplay();

ui->pushButtonStop->setDisabled(true);
ui->pushButtonStart->setDisabled(false);
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

if(start == true) {on_pushButtonStop_clicked();}

robot->~PlayerClient();
if(robot->Connected() == false) {ui->lineEditConn->setText(QString :: fromUtf8("Rozłączony"));
ui->pushButtonConnect->setDisabled(false);
ui->pushButtonDisconnect->setDisabled(true);
ui->pushButtonStart->setDisabled(true);

}

}

//void MainWindow::on_radioButton_pressed()
//{

//}

void MainWindow::on_doubleSpinBoxObsDis_valueChanged(const QString &arg1)
{

}

void MainWindow::on_spinBoxDywer_valueChanged(int arg1)
{

}

void MainWindow::on_doubleSpinBoxDywer_valueChanged(double arg1)
{

}
