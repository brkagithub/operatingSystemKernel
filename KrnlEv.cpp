/*
 * KrnlEv.cpp
 *
 *  Created on: Jun 21, 2021
 *      Author: OS1
 */

#include "KrnlEv.h"
#include "Kernel.h"
#include "IVTEntry.h"
#include "pcb.h"
#include "Schedule.h"
//#include <iostream.h>

KrnlEv::KrnlEv(IVTNo ivtNumberr) {
	lock
	isBlocked = 0;
	ivtNumber = ivtNumberr;
	Kernel::ivtEntries[ivtNumberr]->event = this; //IVTentryju pridruzujemo ovaj event
	myPCB = (PCB*)Kernel::runningPCB; //running PCB pravi event
	unlock
}

void KrnlEv::wait() {
	lock

	if(isBlocked || myPCB != Kernel::runningPCB){
		unlock
		return;
	}

	//isBlocked = 0 i myPCB jeste runningPCB
	myPCB->status = BLOCKED;
	isBlocked = 1;
	unlock

	/*lock
	cout << "Kernel.dispatch";
	unlock*/
	Kernel::dispatch();
}

void KrnlEv::signal(){
	lock
	if(!isBlocked){
		unlock
		return;
	}

	//blokirana je
	myPCB->status = READY;
	isBlocked = 0;
	Scheduler::put(myPCB);
	Kernel::dispatch();
	unlock
}

KrnlEv::~KrnlEv() {
	lock
	Kernel::ivtEntries[ivtNumber]->event = 0;
	unlock
}

