/*
 * Kernel.cpp
 *
 *  Created on: Jun 1, 2021
 *      Author: OS1
 */

#include "Kernel.h"
#include "SCHEDULE.H"
#include <dos.h>
#include <iostream.h>
#include "IdleThr.h"
#include "PCB.h"
#include "Thread.h"
#include "KrnlSem.h"

unsigned tss, tsp, tbp;
void tick(); //za testove
volatile PCB * Kernel::runningPCB = 0;
volatile char Kernel::requestedContextChange = 0;
Time Kernel::runningTimeSlice = 2; //? sta ovde
IdleThr* Kernel::idleThread = 0;
volatile char Kernel::lockFlag = 1;
LList<PCB> Kernel::allPCBs;
LList<KernelSem> Kernel::allSems;
volatile char Kernel::currentUnlimited = 0;
IVTEntry * Kernel::ivtEntries[] = { 0 };

pInterrupt oldTimerRoutine;

void interrupt timer(...){
		if(!Kernel::requestedContextChange){ //ako nismo eksplicitno zahtevali promenu konteksta
			tick(); //tickujemo tajmer - sta tacno radi ? gde cemo da smanjimo trenutnoj niti timeslice ?

			for(Kernel::allSems.toHead(); Kernel::allSems.hasCurr(); Kernel::allSems.toNext()){
				Kernel::allSems.curr->tt->tickWaitingThreads();
			}

			if(!Kernel::currentUnlimited){
			Kernel::runningTimeSlice--; //smanjujemo trenutnu nit
			}

			//verovatno treba ovde da probudimo niti koje su sleepovani sa odredjenim time
			//to do
			//oldTimerRoutine();
		}

		if(Kernel::requestedContextChange || (Kernel::runningTimeSlice == 0 && !Kernel::currentUnlimited)){
			if (Kernel::lockFlag == 1){ //dozvoljen prekid
#ifndef BCC_BLOCK_IGNORE
				asm{
					mov tss, ss
					mov tsp, sp
					mov tbp, bp //ne moze mov running->sp, bp pa mora ovako
				}
#endif
				Kernel::runningPCB->ss = tss; //azuriramo running ss, sp, bp na sistemske ss, sp, bp
				Kernel::runningPCB->sp = tsp; //sp ss bp ce se cesto menjati automatski - pa ne mozemo iskontrolisati to i u runningPCBu
				Kernel::runningPCB->bp = tbp; //zbog toga, pre promene runningPCBa moramo da azuriramo runningSP SS BP na sveze vrednosti

				//&& nije idle nit fali u ifu
				if(Kernel::runningPCB != Kernel::idleThread->idlePCB() && (Kernel::runningPCB->status == NEW ||
				Kernel::runningPCB->status == READY || Kernel::runningPCB->status == RUNNING)){
					Kernel::runningPCB->status = READY;
					Scheduler::put((PCB*)Kernel::runningPCB); //ako nije blokirana ili terminated, stavi je u sched
				}


				Kernel::runningPCB = Scheduler::get();                                       //neku koja nije vec zavrsena

				if(!Kernel::runningPCB)//idle nit koju ne stavljamo u sched
				{
					Kernel::runningPCB = Kernel::idleThread->idlePCB();
				}

				if(Kernel::runningPCB->timeSlice == 0) Kernel::currentUnlimited = 1;
				else Kernel::currentUnlimited = 0;

				Kernel::runningPCB->status = RUNNING; //nova je running
				Kernel::runningTimeSlice = Kernel::runningPCB->timeSlice; //restauriramo preostalo vreme i registre
				tsp = Kernel::runningPCB->sp;
				tss = Kernel::runningPCB->ss;
				tbp = Kernel::runningPCB->bp;


#ifndef BCC_BLOCK_IGNORE
				asm{
					mov ss, tss
					mov sp, tsp
					mov bp, tbp
				}
#endif
				Kernel::requestedContextChange = 0; //resen je
			}
			else { //nije dozvoljen prekid, zapamticemo request svakako
				Kernel::requestedContextChange = 1;
			}
		}

		if(!Kernel::requestedContextChange){
			oldTimerRoutine();
		}
	}

	void Kernel::dispatch(){
#ifndef BCC_BLOCK_IGNORE
		asm cli;

		//cout << "U dispatchu " << endl;
		requestedContextChange = 1; //oznacimo da jesmo trazili promenu i udjemo u timer prekidnu rutinu
		timer();

		asm sti;
#endif
	}

	void Kernel::init(){
#ifndef BCC_BLOCK_IGNORE
		asm cli
		oldTimerRoutine = getvect(0x8); //stara oldtimerroutine
		setvect(0x8, timer); //nova timer
#endif

		Kernel::idleThread = new IdleThr();
		Kernel::idleThread->start(); //samo joj stavi status na ready

		PCB * mainPCB = (new Thread(0x100, 2))->myPCB;


		mainPCB->status = RUNNING;
		Kernel::runningPCB = mainPCB;
		Kernel::runningTimeSlice = 2; //default
		//PCB * ppp = idleThread->myPCB;
#ifndef BCC_BLOCK_IGNORE
		asm sti
#endif
	}

	void Kernel::restore(){
#ifndef BCC_BLOCK_IGNORE
		asm cli
		setvect(0x8, oldTimerRoutine); //restore u 8 ulaz staru
#endif

		//obrisi svu memoriju - sve pcbove, idle..
		for(allSems.toHead(); allSems.hasCurr(); allSems.toNext()){
			delete allSems.getCurr();
		}

		for(allPCBs.toHead(); allPCBs.hasCurr(); allPCBs.toNext()){
			delete allPCBs.getCurr();
		}


#ifndef BCC_BLOCK_IGNORE
		asm sti
#endif
	}

