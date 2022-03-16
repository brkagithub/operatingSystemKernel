/*
 * IdleThread.cpp
 *
 *  Created on: Jun 10, 2021
 *      Author: OS1
 */

#include "IdleThr.h"
#include "Kernel.h"
#include <iostream.h>
#include "PCB.h"

IdleThr::IdleThr() {
	// automatski poziva nadkonstruktor prazni
}

void IdleThr::run(){
	//lock
	//cout << "Usao u idle nit\n";
	//unlock
	volatile int randomBroj = 1;
	while(randomBroj){

	}
}

void IdleThr::start(){
	lock

	myPCB->status = READY; //moralo redefinisanje jer ne sme u scheduler da se stavi

	unlock
}

PCB * IdleThr::idlePCB(){
	return myPCB;
}

IdleThr::~IdleThr() {
	//waitToComplete();
}

