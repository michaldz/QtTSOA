/*
 * Algorithm.h
 *
 *  Created on: 2012-05-20
 *      Author: michal
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_
#include <QThread>

#include "TS.h"

class Algorithm: public TS, public QThread{
public:
			bool onTarget;
            bool onRun;
            bool runAlgo;

	void Test();
	void run();
    bool CheckRun();
	//void Inicjalize();




	Algorithm();
	virtual ~Algorithm();
};

#endif /* ALGORITHM_H_ */
