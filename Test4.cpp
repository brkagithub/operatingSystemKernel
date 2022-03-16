/*#include "kernel.h"
#include "Thread.h"
#include "PCB.h"
#include <iostream.h>
#include "SortedLi.h"
#include "KrnlSem.h"

// 	 Test: razlicita vremena izvrsavanja i velicine steka

volatile Time ts;

void tick()
{
	lock
	cout << "timeSlice=" << ts << endl;
	unlock
}

class TestThread : public Thread
{
private:
	Time myTimeSlice;
public:

	TestThread(StackSize stackSize, Time timeSlice): Thread(stackSize,timeSlice), myTimeSlice(timeSlice) {};
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{
	for(unsigned i=0;i<32000;i++)
	{
		for(unsigned int j=0;j<32000;j++)
		{
			ts = myTimeSlice;
		}
	}
}


int userMain(int argc, char** argv)
{
	lock
	cout << "Test starts.\n";
	unlock

	TestThread t1(64,0), t2(4096,32), t3(1024,16), t4(4096,0);
	t1.start();
	t2.start();
	t3.start();
	t4.start();
	t1.waitToComplete();
	t2.waitToComplete();
	t3.waitToComplete();
	t4.waitToComplete();
	lock
	cout << "Test ends.\n";
	unlock

	LList<int> lista;

	int aa = 1;
	int bb = 2;
	int cc = 3;
	int dd = 4;
	int ee = 5;
	int ff = 6;

	int * a = &aa;
	int * b = &bb;
	int * c = &cc;
	int * d = &dd;
	int * e = &ee;
	int * f = &ff;

	lista.add(a);
	lista.add(b);
	lista.add(c);
	lista.add(d);

	for(lista.toHead(); lista.hasCurr(); lista.toNext()){
		cout << *(lista.curr->tt) << endl;
	}

	cout << endl;

	lista.remove();
	lista.remove();

	for(lista.toHead(); lista.hasCurr(); lista.toNext()){
			cout << *(lista.curr->tt)  << endl;
	}

	cout << endl;

	lista.add(e);
	lista.remove();
	lista.add(f);

	for(lista.toHead(); lista.hasCurr(); lista.toNext()){
		cout << *(lista.curr->tt)  << endl;
	}


	SortedList<timePCB> lista;

	int aa = 1;
	int bb = 2;
	int cc = 3;
	int dd = 4;
	int ee = 5;
	int ff = 6;

	timePCB* a = new timePCB(0, 1);
	timePCB* b = new timePCB(0, 2);
	timePCB* c = new timePCB(0, 3);
	timePCB* d = new timePCB(0, 4);
	timePCB* e = new timePCB(0, 5);
	timePCB* f = new timePCB(0, 6);

	lista.add(f);
	lista.add(c);
	lista.add(e);
	lista.add(b);
	//lista.remove();
	lista.add(d);
	lista.add(b);
	lista.add(a);
	lista.add(f);
	for(lista.toHead(); lista.hasCurr(); lista.toNext()){
			cout << *(lista.curr->tt) << endl;
	}

	return 0;
}
*/

