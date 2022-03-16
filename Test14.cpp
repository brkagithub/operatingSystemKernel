/*
#include <iostream.h>
#include <stdlib.h>
#include "Semaphor.h"
#include "Thread.h"
#include "PCB.h"
#include "Event.h"
#include "KrnlEv.h"
#include "IVTEntry.h"
#include "Kernel.h"

//	Test: brojac sekundi


unsigned t=18;
unsigned seconds = 5;

void secondPast()
{
	if(seconds)
		lock
		cout << seconds << endl;
		unlock
	seconds--;
}

void tick()
{
	t--;
	if(t==0){
		t = 18;
		secondPast();
	}
}



int userMain(int argc, char** argv)
{
	lock
	cout << "Starting test\n";
	unlock
	while(seconds);
	lock
	cout << "ending test\n";
	unlock
	return 0;
}*/
