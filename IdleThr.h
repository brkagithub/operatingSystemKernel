/*
 * IdleThread.h
 *
 *  Created on: Jun 10, 2021
 *      Author: OS1
 */

#ifndef IDLETHR_H_
#define IDLETHR_H_

#include "thread.h"

class IdleThr : public Thread {
public:
	IdleThr();
	virtual ~IdleThr();
	void start();
	PCB * idlePCB();
protected:
	virtual void run();
};

#endif /* IDLETHR_H_ */
