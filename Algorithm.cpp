/*
 * Algorithm.cpp
 *
 *  Created on: 2012-05-20
 *      Author: michal
 */

#include "Algorithm.h"


extern PlayerClient *robot;


extern Position2dProxy *p2dProxy;
//extern LaserProxy laserProxy;
//extern player_pose2d_t target_point;


Algorithm::Algorithm() {
	// TODO Auto-generated constructor stub


    dywerTime = 0;
    distanceToTargetDywer = 0;
    dywerFromGuiCheck = false;

}

Algorithm::~Algorithm() {
	// TODO Auto-generated destructor stub
    p2dProxy->SetSpeed(0,0);

}
/*
void Algorithm::Inicjalize(){

/*
			//enable motors
			p2dProxy.SetMotorEnable(1);
			//request geometries
			p2dProxy.RequestGeom();
			laserProxy.RequestGeom();

			target_point.px = 5;
			target_point.py = 5;
			target_point.pa = 0;

			robot.Read();


}
*/


void Algorithm::Test(){

    if(dywerTime < dywerFromGuiTime || dywerFromGuiCheck == false )

    {
        distanceToTargetDywer = this->distanceToTarget;
	    this->ReadScan();
		this->ReadDistanceToTarget();
		this->ReadDegreesToTarget();
		this->CalculateOffset();
        //this->PrintValuesToConsole(10);
        //this->PrintTargetFunction(10);
        //this->PrintTabuL();
		this->ClearLastScan();

	    //this->CalculateTargetFunction();
        this->CalculateOffset();
	    this->NativeObstacleAvoid1();
        this->TabuSearchMainAlgoritchm();
        onTarget = this->CheckInTarget();
    }
    else if (dywerTime > dywerFromGuiTime && dywerFromGuiCheck == true)
    {
        for(int i = 0; i<dywerRunTime;i++)
        {
        this->ReadScan();
        this->ReadDistanceToTarget();
        this->ReadDegreesToTarget();
        this->CalculateOffset();
        //this->PrintValuesToConsole(10);
        //this->PrintTargetFunction(10);
        //this->PrintTabuL();
        this->ClearLastScan();

        //this->CalculateTargetFunction();
        this->CalculateOffset();

        //Nadanie ruchu w przeciwną stronę
            if(i == 0) {this->MoveTo(0.00,45); this->sleep(4); }
        this->MoveTo(0.3,0);
        this->NativeObstacleAvoid1();

        //ToDO dodać ruch w losowym kierunku

        onTarget = this->CheckInTarget();
        this->sleep(0.1);
        }

        dywerTime = 0;
    }







}
void Algorithm::run(){



    do{
         onRun = true;

        robot->Read();




            Test();




            this->sleep(0.1);


            if(distanceToTargetDywer < this->distanceToTarget)
            {

                dywerTime = dywerTime + 0.1;

            }
            else
            {
            dywerTime = 0;
            }


            if (onTarget == true || runAlgo == false)
            {
            onRun = false;
            break;
            }

    }while(runAlgo);


}
bool Algorithm::CheckRun(){

return onRun;
}
void Algorithm::DywerInit(bool radio, int spin,double run){

    dywerFromGuiCheck = radio;
    dywerFromGuiTime = spin;
    dywerRunTime = run*10;

}
