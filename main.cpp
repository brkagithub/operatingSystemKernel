/*
 * main.cpp
 *
 *  Created on: Jun 10, 2021
 *      Author: OS1
 */

#include "Kernel.h"
#include <iostream.h>

extern int userMain(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	/*cout <<"AAAA";
	cout<<"main.cpp pocetak\n";*/

	Kernel::init();

	int ret = userMain(argc, argv);


	int z = 0;

	Kernel::restore();

	return ret;
}
