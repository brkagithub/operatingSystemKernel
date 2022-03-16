/*#include "kernel.h"
#include <iostream.h>
#include <stdlib.h>
#include "Semaphor.h"
#include "Thread.h"
#include "PCB.h"


//Test: Semafori sa spavanjem 2


int t=-1;

Semaphore s(0);

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
	//syncPrintf("Thread %d waits for %d units of time.\n",getId(),waitTime);
	cout << "Thread " << getId() << " waits for " << waitTime << " units of time.\n";
	unlock
	int r = s.wait(waitTime);
	s.signal();
	lock
	//syncPrintf("Thread %d finished: r = %d\n", getId(),r);
	cout << "Thread " << getId() << " finished: r = " << r << endl;
	unlock
}

void tick()
{
	t++;
	if(t){
		//syncPrintf("%d\n",t);
		lock
		cout << t << "xxx" << endl;
		unlock
	}
}

int userMain(int argc, char** argv) // poenta testa - main se blokira, posle 5 timesliceova, prvo treba da se odblokira 10 pa chain reakcija
{
	lock
	cout << "Test starts.\n";
	unlock
	TestThread t1(15),t2(10),t3(30);
	t1.start();
	t2.start();
	t3.start();

	s.wait(5);
	s.signal();
	s.wait(0);
	s.signal();
	lock
	cout << "Test ends.\n";
	unlock
	return 0;
}*/
