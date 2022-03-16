/*#include <iostream.h>
#include <stdlib.h>
#include "Semaphor.h"
#include "Thread.h"
#include "PCB.h"
#include "Event.h"
#include "KrnlEv.h"
#include "IVTEntry.h"
#include "Kernel.h"

//	Test: dogadjaji


#include <iostream.h>
#include <stdlib.h>

PREPAREENTRY(9,1);

Semaphore* mutex = 0;
Semaphore* sleepSem = 0;

void tick() {}


class Znak : public Thread
{
public:
	Znak(char znak, int n) : Thread(), znak(znak), n(n) {}
	virtual ~Znak() { waitToComplete(); }
	
	void run()
	{
		// for (long i = 0; i < 100000; i++)
		for (int i = 0; i < n; i++)
		{
			if (mutex->wait(1)) {
				lock
				//cout << "mutex val: " << mutex->val() << endl;
				cout << znak;
				unlock
				//cout << "X";
				mutex->signal();
				lock
				//cout << "mutex val: " << mutex->val() << endl;
				unlock
			}

			// for (int j = 0; j < 10000; j++)
				// for (int k = 0; k < 10000; k++);
			Time sleepTime = 2 + rand() % 8;
			lock
			//cout << "sleepTime: " << sleepTime << endl;
			//cout << "sleepSem val: " << sleepSem->val() << endl;
			unlock
			sleepSem->wait(sleepTime);
			lock
			//cout << "sleepSem val: " << sleepSem->val() << endl;
			unlock
			
			// dispatch();
		}
		lock
		//cout << "mutex val: " << mutex->val() << endl;
		unlock
		if (mutex->wait(1)) {
			lock
			cout << endl << znak << " finished" << endl;
			unlock
			mutex->signal();
			lock
			//cout << "mutex val: " << mutex->val() << endl;
			unlock
		}
	}
	
private:
	char znak;
	int n;
	
};


class Key : public Thread {
public:
	Key(int n) : Thread(), n(n) { }
	virtual ~Key() { waitToComplete(); }
	
	void run() {
		Event e(9);

		for (int i = 0; i < n; i++) {
			if (mutex->wait(1)) {
				lock
				cout << endl << "key waiting " << (i + 1) << endl;
				unlock
				mutex->signal();
			}
			
			e.wait();

			if (mutex->wait(1)) {
				lock
				cout << endl << "key continue " << (i + 1) << endl;
				unlock
				mutex->signal();
			}
			
			sleepSem->wait(5);
		}
		
		if (mutex->wait(1)) {
			lock
			cout << endl << "key finished" << endl;
			unlock
			mutex->signal();
		}
	}
	
private:
	int n;
	
};


int userMain(int argc, char* argv[]) {
	mutex = new Semaphore(1);
	sleepSem = new Semaphore(0);
	
	Znak* a = new Znak('a', 10);
	Znak* b = new Znak('b', 15);
	Znak* c = new Znak('c', 20);
	Key* k = new Key(150);
	
	a->start();
	b->start();
	c->start();
	k->start();
	
	delete a;

	//cout << "Deleted a" << endl;

	delete b;
	delete c;
	delete k;
	
	if (mutex->wait(1)) {
		lock
		cout << endl << "userMain finished" << endl;
		unlock
		mutex->signal();
	}
	
	delete sleepSem;
	delete mutex;
	
	return 0;
}*/
