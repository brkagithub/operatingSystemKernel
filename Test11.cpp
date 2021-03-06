/*#include "kernel.h"
#include <iostream.h>
#include <stdlib.h>
#include "Semaphor.h"
#include "Thread.h"
#include "PCB.h"


 //	 Test: Semafori sa spavanjem 3


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
	cout << "Thread " << getId() << "waits for " << waitTime << " units of time.\n";
	unlock
	int r = s.wait(waitTime);
	s.signal();
	lock
	cout << "Thread " << getId() << " finished: r = " << r << endl;
	unlock
}

void tick()
{

	//t++;
	//if(t)
	//	syncPrintf("%d\n",t);

}


#include <iostream.h>

Semaphore* mutex = 0;

class Znak : public Thread
{
public:
	Znak(char znak, int n) : Thread(), znak(znak), n(n) {}
	virtual ~Znak() { waitToComplete(); }

	void run()
	{
		for (long i = 0; i < 10000; i++)
		{
			if (mutex->wait(n)) {
				cout << znak;
				mutex->signal();
			}

		}

		if (mutex->wait(n)) {
			cout << endl << znak << " finished" << endl;
			mutex->signal();
		}
	}

private:
	char znak;
	int n;

};


int userMain(int argc, char* argv[]) {
	mutex = new Semaphore(1);

	Znak* a = new Znak('a', 10);
	Znak* b = new Znak('b', 15);
	Znak* c = new Znak('c', 20);

	a->start();
	b->start();
	c->start();

	delete a;
	delete b;
	delete c;

	if (mutex->wait(1)) {
		cout << endl << "userMain finished" << endl;
		mutex->signal();
	}

	delete mutex;



	return 0;
}*/
