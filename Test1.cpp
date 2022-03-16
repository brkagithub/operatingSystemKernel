/*#include "kernel.h"
#include "Thread.h"
#include "PCB.h"
#include <iostream.h>

//Test cekanje

class TestThread : public Thread
{
public:

	TestThread(): Thread() { };
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
	cout << "Thread " << getId() << ": loop1 starts\n";
	unlock

	for(int i=0;i<32000;i++)
	{
		for (int j = 0; j < 32000; j++);
	}

	lock
	cout << "Thread " << getId() << ": loop1 ends, dispatch\n";
	unlock

	Kernel::dispatch();

	lock
	cout << "Thread " << getId() << ": loop2 starts\n";
	unlock

	for (int k = 0; k < 20000; k++);

	lock
	cout << "Thread " << getId() << ":  loop2 ends\n";
	unlock
}

class WaitThread: public Thread
{
private:
	TestThread *t1_,*t2_;

public:
	WaitThread(TestThread *t1, TestThread *t2): Thread()
	{
		t1_ = t1;
		t2_ = t2;
	};

	~WaitThread()
		{
			waitToComplete();
		}

protected:

	void run()
	{
		lock
		cout << "Starting tests...\n";
		unlock

		t1_->waitToComplete();
		lock
		cout << "Test 1 completed!\n";
		unlock

		t2_->waitToComplete();
		lock
		cout << "Test 2 completed!\n";
		unlock
	}
};

void tick() {}


int userMain(int argc, char** argv)
{
	lock
	cout << "User main starts\n";

	TestThread t1,t2;

	WaitThread w(&t1,&t2);
	t1.start();
	t2.start();
	w.start();
	w.waitToComplete();

	lock
	cout << "User main ends\n";
	unlock

	return 16;
}
*/


