/*
 * Event.h
 *
 *  Created on: Jun 21, 2021
 *      Author: OS1
 */

// File: event.h
#ifndef _event_h_
#define _event_h_

#include "IVTEntry.h"

typedef void interrupt (*pInterrupt)(...);
typedef unsigned char IVTNo;

class KrnlEv;

class Event {
public:
	Event (IVTNo ivtNo);
	~Event ();

	void wait ();
protected:
	friend class KrnlEv;
	void signal(); // can call KrnlEv
private:
	KrnlEv* myImpl;
};

#define PREPAREENTRY(numEntry, callOld)\
	void interrupt inter##numEntry(...);\
	IVTEntry newEntry##numEntry(numEntry, inter##numEntry);\
	void interrupt inter##numEntry(...){\
		newEntry##numEntry.signal();\
		if(callOld) newEntry##numEntry.callOldRoutine();\
	}
//IVTEntry newEntry5(5, inter5) - 5 je ulaz, a inter5 metoda interrupt koja radi signal i pozivanje stare iz petog ulaza
#endif
