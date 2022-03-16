/*#include "kernel.h"
#include "Thread.h"
#include "PCB.h"
#include <iostream.h>

//	Test: asinhrono preuzimanje

class TestThread : public Thread
{
public:

	TestThread(): Thread() {};
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
	cout << "Thread " << getId() << ": loop1 starts\n" << endl;
	unlock

	for(int i=0;i<32000;i++)
	{
		for (int j = 0; j < 32000; j++);
	}

	lock
	cout << "Thread " << getId() << ": loop1 ends, dispatch\n" << endl;
	unlock


	Kernel::dispatch();

	lock
	cout << "Thread " << getId() << ":  loop2 starts\n" << endl;
	unlock

	for (int k = 0; k < 20000; k++);

	lock
	cout << "Thread " << getId() << ":  loop2 ends\n" << endl;
	unlock


}



void tick(){}

int userMain(int argc, char** argv)
{
	lock
	cout << "User main starts\n" << endl;
	unlock

	TestThread t1,t2;
	t1.start();
	t2.start();

	lock
	cout << "User main ends\n" << endl;
	unlock

	return 16;
}

*/
