/*
 * Semaphor.cpp
 *
 *  Created on: Jun 12, 2021
 *      Author: OS1
 */

#include "Semaphor.h"
#include "Kernel.h"
#include "KrnlSem.h"

Semaphore::Semaphore(int init) {
	myImpl = new KernelSem(init, this);
}

int Semaphore::wait(Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
}

void Semaphore::signal(){
	myImpl->signal();
}

int Semaphore::val() const {
	return myImpl->val();
}

Semaphore::~Semaphore() {
	lock
	Kernel::allSems.remove(myImpl);
	delete myImpl;
	unlock
}
