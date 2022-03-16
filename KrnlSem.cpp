/*
 * KrnlSem.cpp
 *
 *  Created on: Jun 12, 2021
 *      Author: OS1
 */

#include "KrnlSem.h"
#include "Kernel.h"
#include "PCB.h"
#include "Schedule.h"

KernelSem::KernelSem(int init, Semaphore * mmySem) {
	value = init;
	mySem = mmySem;
	Kernel::allSems.add(this);
}

int KernelSem::val() const{
	return this->value;
}

int KernelSem::wait(Time maxTimeToWait){ //0 <=> nije vremenski ogranicena
	lock
	value--;

	if(value >= 0){
		unlock
		return 1;
	}

	Kernel::runningPCB->status = BLOCKED;

	if(maxTimeToWait != 0) //lista blokiranih niti s vremenom
	{
		waitingOnTime.add(new timePCB((PCB*)Kernel::runningPCB, maxTimeToWait));
		//waitingOnTime2.add(new timePCB((PCB*)Kernel::runningPCB, maxTimeToWait));
	}
	else //lista blokiranih niti neograniceno
	{
		waitingOnSem.add((PCB*)Kernel::runningPCB);
	}

	unlock
	Kernel::dispatch();

	if(Kernel::runningPCB->deblockedBySignal) return 1;
	else return 0;
}

void KernelSem::signal(){
	lock
	value++;

	if(waitingOnSem.count() > 0){
		PCB * toUnblock = waitingOnSem.getHead();
		toUnblock->deblockedBySignal = 1;
		toUnblock->status = READY;
		Scheduler::put(toUnblock);
		waitingOnSem.remove();
		unlock
		return;
	}
	/*else if(waitingOnTime.count() > 0){
		timePCB* temp = waitingOnTime.getHead();
		waitingOnTime.remove();
		PCB * toUnblock = temp->pcb;
		toUnblock->deblockedBySignal = 1;
		toUnblock->status = READY;
		Scheduler::put(toUnblock);
		unlock
		return;*/
		/*
		cout << "::::::::::::ODBLOKIRAM TAIL::::::::::::::"<<endl;
		timePCB* temp = waitingOnTime.getTail();
		waitingOnTime.removeFromEnd();
		PCB * toUnblock = temp->pcb;

		cout << "::::ID = " << toUnblock->getID() << endl;
		toUnblock->deblockedBySignal = 1;
		toUnblock->status = READY;
		Scheduler::put(toUnblock);
		unlock
		return;
	}*/
	else if(waitingOnTime.count() > 0){
			timePCB* temp = waitingOnTime.getHead();
			PCB * toUnblock = temp->pcb;
			toUnblock->deblockedBySignal = 1;
			toUnblock->status = READY;
			Scheduler::put(toUnblock);
			waitingOnTime.remove();
			unlock
			return;
	}
	else {
		//value--; //ako nemamo sta odblokirati
		unlock
		return;
	}
}

void KernelSem::tickWaitingThreads(){
	lock
	for(waitingOnTime.toHead(); waitingOnTime.hasCurr(); waitingOnTime.toNext()){
		waitingOnTime.curr->tt->time = waitingOnTime.curr->tt->time-1;
		if(waitingOnTime.curr->tt->time == 0){
			value++;
			timePCB* temp = waitingOnTime.getHead();
			PCB * toUnblock = temp->pcb;
			toUnblock->deblockedBySignal = 0;
			//cout << "deblockedBySignal = 0" << endl;
			toUnblock->status = READY;
			Scheduler::put(toUnblock);
			waitingOnTime.remove();
			waitingOnTime.toHead();
		}
	}

	/*for(waitingOnTime2.toHead(); waitingOnTime2.hasCurr(); waitingOnTime2.toNext()){
			waitingOnTime2.curr->tt->time = waitingOnTime2.curr->tt->time-1;
			if(waitingOnTime2.curr->tt->time == 0){
				value++;
				timePCB* temp = waitingOnTime2.remove(waitingOnTime2.curr->tt);
				PCB * toUnblock = temp->pcb;
				//waitingOnTime.remove();
				toUnblock->deblockedBySignal = 0;
				//cout << "deblockedBySignal = 0" << endl;
				toUnblock->status = READY;
				Scheduler::put(toUnblock);
			}
		}*/
	unlock
}

KernelSem::~KernelSem() {
	while(value!=0) this->signal();

	//Kernel::allSems.remove(this);
}
