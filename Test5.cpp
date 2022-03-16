/*
#include "kernel.h"
#include "Thread.h"
#include "PCB.h"
#include <iostream.h>



// 	 Test: frekventni dispatch


const int n = 10;

void tick(){}

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
	for(int i=0;i<32000;i++)
	{
		for(int j=0;j<16;j++){
		Kernel::dispatch();
		lock
		cout << ".";
		//printf(".");
		unlock
		}
	}
}


int userMain(int argc, char** argv)
{
	lock
	cout << "Test starts.\n" << endl;
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
	cout << "Test ends.\n" << endl;
	unlock

	return 0;
}
*/
