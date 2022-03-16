// File: thread.h
#ifndef _thread_h_
#define _thread_h_

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;

typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms

typedef int ID;

class PCB; // Kernel's implementation of a user's thread

class Thread {
public:
	 void start(); //start metoda

	 void waitToComplete(); //blokira nit iz koje se poziva, dok nit nad kojom se poziva ne zavrsi izvrsavanje

	 virtual ~Thread();

	 ID getId(); //id za pozivajucu

	 static ID getRunningId(); //static metoda vrati id running niti

	 static Thread * getThreadById(ID id); // static metoda vrati Thread * niti po prosledjenom ID

	 //virtual void run() {}

protected:
	 friend class PCB;
	 friend class Kernel;
	 friend class IdleThr;

	 Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);

	 virtual void run() {}

private:
	 PCB* myPCB; //implementacija niti unutar jezgra - realizuje datu korisnicku nit
};

void dispatch ();

#endif
