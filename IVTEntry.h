/*
 * IVTEntry.h
 *
 *  Created on: Jun 21, 2021
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

typedef void interrupt (*pInterrupt)(...);
typedef unsigned char IVTNo;

class KrnlEv;

class IVTEntry {
public:
	static IVTEntry * getIVTEntry(IVTNo IVTnumber);

	IVTEntry(IVTNo ivtNumberr, pInterrupt newRoutine);
	~IVTEntry();

	IVTNo ivtNumber;
	KrnlEv* event;
	pInterrupt oldRoutine;

	void callOldRoutine();

	void signal();
};

#endif /* IVTENTRY_H_ */
