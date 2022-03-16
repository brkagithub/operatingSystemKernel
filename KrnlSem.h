/*
 * KrnlSem.h
 *
 *  Created on: Jun 12, 2021
 *      Author: OS1
 */

#ifndef KRNLSEM_H_
#define KRNLSEM_H_

#include "Semaphor.h"
#include "List.h"
#include <iostream.h>
#include "Sortedli.h"

class PCB;

//struct PCBTime; //pcb sa vremenom - pa njegova lista koja ce biti sortirana za pcbove koji su blokirani sa vremenom na semaforu
struct timePCB {
	PCB * pcb;
	volatile int time;

	timePCB(PCB * pcbb, int ttime){
		pcb = pcbb;
		time = ttime;
	}

	int operator > (const timePCB & other) const{
		if (this->time > other.time) return 1;
		else return 0;
	}

	int operator < (const timePCB & other) const{
			if (time < other.time) return 1;
			else return 0;
	}

	int operator >= (const timePCB & other) const{
			if( time >= other.time ) return 1;
			else return 0;
	}

	int operator <= (const timePCB & other) const{
			if (time <= other.time) return 1;
			else return 0;
	}

	friend ostream& operator <<(ostream& it, const timePCB & p){
		it << p.time;
		return it;
	}
};

class KernelSem {
public:
	KernelSem(int init=1, Semaphore * mmySem);

	LList<PCB> waitingOnSem;
	SortedList<timePCB> waitingOnTime;
	LList<timePCB> waitingOnTime2;

	virtual ~KernelSem();

	int wait(Time maxTimeToWait);

	void signal();

	int val () const;

	int value;

	void tickWaitingThreads();

	Semaphore * mySem;
};

#endif /* KRNLSEM_H_ */
