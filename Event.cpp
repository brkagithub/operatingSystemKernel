/*
 * Event.cpp
 *
 *  Created on: Jun 21, 2021
 *      Author: OS1
 */
#include "Kernel.h"
#include "Event.h"
#include "KrnlEv.h"

Event::Event(IVTNo ivtNo) { //pravimo event sa svojim ulazom u IVT tabelu iz kog ce pozivati prekidnu rutinu
	lock
	myImpl = new KrnlEv(ivtNo);
	unlock
}

void Event::wait(){
	myImpl->wait(); //pozivamo implementaciju
}

void Event::signal(){
	myImpl->signal(); //pozivamo implementaciju
}

Event::~Event() {
	lock
	delete myImpl; //brisemo implementaciju
	unlock
}

