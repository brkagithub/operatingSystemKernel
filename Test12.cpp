/*#include "kernel.h"
#include <iostream.h>
#include <stdlib.h>
#include "Semaphor.h"
#include "Thread.h"
#include "PCB.h"


// 	 Test: Semafori sa spavanjem 4


int t=-1;

const int n=15;

Semaphore s(1);

class TestThread : public Thread
{
private:
	Time waitTime;

public:

	TestThread(Time WT): Thread(), waitTime(WT){}
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
	cout << "Thread " << getId() << " waits for " << waitTime << " units of time.\n";
	unlock
	int r = s.wait(waitTime);
	if(getId()%2)
		s.signal();
	lock
	cout << "Thread " << getId() << " finished: r = " << r << endl;
	unlock
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
	TestThread* t[n];
	int i;
	for(i=0;i<n;i++)
	{
		t[i] = new TestThread(5*(i+1));
		t[i]->start();
	}
	for(i=0;i<n;i++)
	{
		t[i]->waitToComplete();
	}
	delete t;
	lock
	cout << "Test ends.\n";
	unlock
	return 0;
}*/
