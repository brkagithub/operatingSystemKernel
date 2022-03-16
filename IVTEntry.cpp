/*
 * IVTEntry.cpp
 *
 *  Created on: Jun 21, 2021
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "Kernel.h"
#include "dos.h"
#include "KrnlEv.h"

IVTEntry * IVTEntry::getIVTEntry(IVTNo IVTnumber){
	return Kernel::ivtEntries[IVTnumber];
}

IVTEntry::IVTEntry(IVTNo ivtNumberr, pInterrupt newRoutine) {
	lock
	event = 0;
	ivtNumber = ivtNumberr;
#ifndef BCC_BLOCK_IGNORE
	oldRoutine = getvect(ivtNumberr); //staru rutinu cuvamo
	setvect(ivtNumberr, newRoutine); //novu postavljamo
#endif
	Kernel::ivtEntries[ivtNumber] = this;
	unlock
}

void IVTEntry::signal(){
	if(!event) return;
	event->signal();
}

void IVTEntry::callOldRoutine(){
	//lock
	if(!oldRoutine) return;
	oldRoutine();
	//unlock
}

IVTEntry::~IVTEntry() {
	lock
#ifndef BCC_BLOCK_IGNORE
	setvect(ivtNumber, oldRoutine); //vracamo staru rutinu
#endif
	Kernel::ivtEntries[ivtNumber] = 0;
	unlock
}

