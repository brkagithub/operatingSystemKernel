/*
 * Kernel.h
 *
 *  Created on: Jun 1, 2021
 *      Author: OS1
 */

#include "List.h"

#ifndef KERNEL_H_
#define KERNEL_H_

typedef void interrupt (*pInterrupt)(...);

typedef unsigned int Time; // time, x 55ms

class PCB;
class IdleThr;
class KernelSem;
class IVTEntry;

#define lock Kernel::lockFlag=0;
#define unlock Kernel::lockFlag=1; if(Kernel::requestedContextChange) Kernel::dispatch();

class Kernel{
	friend void interrupt timer(...);

public:
	static IVTEntry * ivtEntries[256];

	static IdleThr * idleThread;

	static volatile char currentUnlimited;

	static LList<PCB> allPCBs;

	static LList<KernelSem> allSems;

	static volatile char lockFlag; //valjda moze char, volatile jer ga koristi vise niti da ne bude optimizacije

	static volatile char requestedContextChange; //koristi vise niti, volatile => nema optimizacije !!

	//da li da cuvamo sve pcbove pa da ih brisemo posle ?

	volatile static PCB * runningPCB; //volatile ?? -ne zelimo optimizaciju!

	static Time runningTimeSlice;

	static void dispatch(); //sinhrona promena konteksta

	static void init(); //inicijalizuj novu prekidnu rutinu

	static void restore(); //vrati staru prekidnu rutinu
};



#endif /* KERNEL_H_ */
