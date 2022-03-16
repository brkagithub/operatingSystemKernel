// File: thread.h
#ifndef _pcb_h_
#define _pcb_h_

#include "List.h"

enum Status { NEW, READY, RUNNING, BLOCKED, TERMINATED};

//#include "Thread.h"
//#include "Kernel.h" //mozda ne mora ovde

typedef unsigned int Time; // time, x 55ms
typedef unsigned long StackSize;
typedef void interrupt (*pInterrupt)(...);
typedef int ID;

//Time - unsigned int, StackSize - unsigned long, ID - int

class Thread;


class PCB {

public:
	friend class Thread;

	static ID nextID; //sledeca nit

	unsigned * stack; //pok na stek
	unsigned ss, sp, bp; //ss - stek segment, sp - njegov offsetni, moze i bp biti

	char deblockedBySignal;

	Time timeSlice;
	//Time timeRemaining;
	//Time timeToWait;
	StackSize stackSize;
	Status status;
	ID id; //id niti

	Thread * myThread;
	LList<PCB> waitingList; //samo PCB jer je lista T*, lista koji cekaju na ovo


	PCB(Thread * mmyThread, StackSize sstackSize, Time ttimeSlice);

	void start();

	void waitToComplete();

	static void wrapper();

	ID getID();

	//static PCB * runningPCB; //ipak u kernelu

	//static Time counter; //koliko traje trenutna nit - ipak u kernelu


	~PCB();
};

#endif
