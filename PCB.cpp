/*
 * PCB.cpp
 *
 *  Created on: Jun 1, 2021
 *      Author: OS1
 */

#include <dos.h>
#include <iostream.h>
#include "PCB.h"
#include "SCHEDULE.H"
#include "List.h"
#include "Kernel.h"
#include "Thread.h"

ID PCB::nextID = 0;

void PCB::wrapper(){
	Kernel::runningPCB->myThread->run();

	lock
	Kernel::runningPCB->status = TERMINATED;

	//for(Node * h = this->waitingList.head; h!=0; h=h->)
	for(((PCB*)Kernel::runningPCB)->waitingList.toHead(); ((PCB*)Kernel::runningPCB)->waitingList.hasCurr(); ((PCB*)Kernel::runningPCB)->waitingList.toNext()){
		PCB * p = ((PCB*)Kernel::runningPCB)->waitingList.getPointer();
		p->status = READY;
		Scheduler::put(p);
	}

	/*while(waitingList.hasCurr()){ //treba li ovo ? svakako samo jednom start metoda
		waitingList.remove();     //tako da za ubuduce nije bitno
	}*/

	unlock

	Kernel::dispatch(); //jer mu nismo dali callback mora
}

PCB::PCB(Thread * mmyThread, StackSize sstackSize, Time ttimeSlice) : myThread(mmyThread), timeSlice(ttimeSlice){
	lock
	this->deblockedBySignal = 0;
	this->stackSize = sstackSize / sizeof(unsigned);

	this->id = nextID++;

	this->status = NEW;

	this->stack = new unsigned[this->stackSize];
	this->stack[this->stackSize - 1] = 0x200; //redosled - PSW pa PC (CS pa IP, jer niza adr = nizi bit)
#ifndef BCC_BLOCK_IGNORE
	this->stack[this->stackSize - 2] = FP_SEG(PCB::wrapper); //pitamo se - sta je PC kad
	this->stack[this->stackSize - 3] = FP_OFF(PCB::wrapper); //odgovor je funkcija Wrapper koju podmecemo da pozove run threada
#endif
	//-1 do -11 registri ax, bx, cx, dx, es, ds, si, di.. za njih vrednost moze biti random na pocetku..

#ifndef BCC_BLOCK_IGNORE
	this->ss = FP_SEG(this->stack + this->stackSize - 12);
	this->sp = FP_OFF(this->stack + this->stackSize - 12);
#endif

	this->bp = this->sp; //na pocetku BP pokazuje na SP

	Kernel::allPCBs.add(this);

	unlock
}

ID PCB::getID(){
	return this->id;
}

void PCB::start(){
	lock

	if(status!=NEW) return; //ne moze vise puta da se pozove

	status = READY;

	//Kernel::allPCBs.add(this);

	Scheduler::put(this); //stavljamo nasu nit koja je ready u scheduler

	unlock
}

void PCB::waitToComplete(){ //blokira nit iz koje se poziva, dok nit nad kojom se poziva ne zavrsi izvrsavanje
	lock //ne zelimo da nas neko prekine dok ne blokiramo nit

	if(status != TERMINATED && this != Kernel::runningPCB){
		Kernel::runningPCB->status = BLOCKED; //iz koje se poziva (running) se blokira
		this->waitingList.add((PCB*)Kernel::runningPCB); //dodali smo u listu cekanja ove niti trenutnu runningPCB
		Kernel::dispatch(); //zelimo nekom drugi preuzme
	}

	unlock //ako je nas status terminated, nista ne radimo, jer je nit gotova
}

PCB::~PCB(){
	lock
	status = TERMINATED;
	if(stack) delete[] stack; //brisemo memoriju a to je stack
	unlock
}
