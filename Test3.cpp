/*#include "kernel.h"
#include "Thread.h"
#include "PCB.h"
#include <iostream.h>


//	Test: dohvatanje i pretraga po ID

const int n = 16;

void tick(){}

class TestThread : public Thread
{
public:

	TestThread(): Thread(4096,2) {};
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{

	int buffer=2;

	for(int i=0;i<32000;i++)
	{
		buffer = 4096/2048;
		for (int j = 0; j < 1024; j++)
		{
			buffer = buffer*2;
			if(buffer%2)
				buffer = 2;
		}
	}

}


int userMain(int argc, char** argv)
{
	lock
	cout << "Test starts: " << n << " threads."<<endl;
	unlock

	int i;
	TestThread threads[n];
	for(i=0;i<n;i++)
	{
		threads[i].start();
	}
	for(i=0;i<n;i++)
	{
		threads[i].waitToComplete();
		lock
		cout << Thread::getThreadById(i+10)->getId() << ". Done!\n" <<endl;
		unlock
	}
	lock
	cout << "Test ends: " <<endl;
	unlock
	return 0;
}
*/

