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


	//if (onTarget == false){
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
	//}
	//else
	//{
	//	this->MoveTo(0,0);
	//	onTarget = this->CheckInTarget();

	//}


}
void Algorithm::run(){



    do{


        robot->Read();




            Test();




            this->sleep(0.1);
            onRun = true;
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
