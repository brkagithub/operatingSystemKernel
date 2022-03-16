/*
 * Thread.cpp
 *
 *  Created on: Jun 1, 2021
 *      Author: OS1
 */
#include "Thread.h"
#include "PCB.h"
#include "Kernel.h"
#include <iostream.h>

Thread::Thread(StackSize stackSize, Time timeSlice){
	lock
	myPCB = new PCB(this, stackSize, timeSlice);
	unlock
}

void Thread::start(){
	myPCB->start();
}

void Thread::waitToComplete(){
	myPCB->waitToComplete();
}

Thread::~Thread(){
	waitToComplete();
	lock
	delete myPCB; //izbaciti iz globalnog niza svih pcb ?
	unlock
}

ID Thread::getId(){
	return myPCB->getID();
}

ID Thread::getRunningId(){
	return ((PCB*)Kernel::runningPCB)->getID();
}

Thread * Thread::getThreadById(ID id){
	lock
	for(Kernel::allPCBs.toHead(); Kernel::allPCBs.hasCurr(); Kernel::allPCBs.toNext()){
			PCB * p = Kernel::allPCBs.getPointer();
			if(p->id == id){
				unlock
				return p->myThread;
			}
	}
	unlock
	return 0;
}

void dispatch(){
#ifndef BCC_BLOCK_IGNORE
		asm cli;

		//cout << "U dispatchu " << endl;
		Kernel::requestedContextChange = 1; //oznacimo da jesmo trazili promenu i udjemo u timer prekidnu rutinu
		timer();

		asm sti;
#endif
}
