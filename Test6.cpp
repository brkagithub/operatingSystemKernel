/*#include "kernel.h"
#include "Thread.h"
#include "PCB.h"
#include <iostream.h>


// 	 Test: idleThread



void tick(){}

class TestThread : public Thread
{
private:
	TestThread *t;

public:

	TestThread(TestThread *thread): Thread(), t(thread){}
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{
	t->waitToComplete();
}


int userMain(int argc, char** argv)
{
	lock
	cout << "Test starts.\n";
	unlock

	TestThread *t1,*t2;
	t1 = new TestThread(t2);
	t2 = new TestThread(t1);
	t1->start();
	t2->start();
	delete t1;
	delete t2;

	lock
	cout << "Test ends.\n";
	unlock

	return 0;
}*/


