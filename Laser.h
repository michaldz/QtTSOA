/*
 * Laser.h
 *
 *  Created on: 2012-05-20
 *      Author: michal
 */

#ifndef LASER_H_
#define LASER_H_
#include <stdio.h>
#include <limits>
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include "Sick.h"
#include <libplayerc++/playerc++.h>
#include <QThread>
using namespace PlayerCc;
class Laser {

private:
	std::vector <Sick> samplesVector;
	double distanceX;
	double distanceY;
public:
    double distanceToTarget;
    double degreesToTarget;
    double angleToTarget;
    double robotOrientationInDegrees;
    double laserRange;
    bool nativeObstacleAvoid;
    double tolerancy;

	void ReadScan();
	void ClearLastScan();
	void PrintValuesToConsole();
	void PrintValuesToConsole(int);
    bool CheckInTarget();
    void Robotorientation();
    void ReadDistanceToTarget();
    void ReadDegreesToTarget();
	int SickResolution();
	int SickListMaxSize();
	double ReturnSickListSum(int);
	double ReturnSickSize(int);
	double ReturnLastScan(int);
	void MoveTo(double,double); // set meters,angle per sec
	void NativeObstacleAvoid();
	void NativeObstacleAvoid1();
    double GetSpeed();
    double GetX();
    double GetY();

	Laser();
	virtual ~Laser();
};

#endif /* LASER_H_ */
