/*#include "kernel.h"
#include <iostream.h>
#include <stdlib.h>
#include "Semaphor.h"
#include "Thread.h"
#include "PCB.h"

// 	 Test: Semafori sa spavanjem


const int n = 1;
int t=-1;

Semaphore s(0);

class TestThread : public Thread
{
public:

	TestThread(): Thread(){}
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{
	lock
	cout << "Thread waits for 100 units of time...\n";
	unlock
	t=0;
	s.wait(100);
	lock
	cout << "Thread finished.\n";
	unlock
	s.signal();
}

void tick()
{
	t++;
	if(t){
		lock
		cout << t << endl;
		unlock
	}
}

int userMain(int argc, char** argv)
{
	lock
	cout << "Test starts.\n";
	unlock
	TestThread t[n];
	int i;
	for(i=0;i<n;i++)
	{
		t[i].start();
	}
	for(i=0;i<n;i++)
	{
		t[i].waitToComplete();
	}
	lock
	cout << "Test ends.\n";
	unlock
	return 0;
}*/
