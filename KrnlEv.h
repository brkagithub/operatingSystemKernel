/*
 * KrnlEv.h
 *
 *  Created on: Jun 21, 2021
 *      Author: OS1
 */

#ifndef KRNLEV_H_
#define KRNLEV_H_

typedef unsigned char IVTNo;

class PCB;

class KrnlEv {
public:
	KrnlEv(IVTNo ivtNumberr); //pravimo implementaciju sa brojem ulaza
	~KrnlEv();

	void wait(); //binarni semafor sa wait i signal - wait samo ako je bas taj PCB napravio event
	void signal();

	char isBlocked;

	IVTNo ivtNumber;
	PCB * myPCB;
};

#endif /* KRNLEV_H_ */
