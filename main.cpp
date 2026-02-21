#include<iostream>
#include"SharedlockingTest.h"

int main()
{
	cout << "Treading Test to run:\n";
	cout << "1. sharedLockTest\n";
	cout << "1. sharedLockTest\n";
	cout << "Please input the test number to run:\n";
	int testNum;
	ThreadTest* Threadtest = nullptr;
	cin >> testNum;
	switch (testNum)
	{
	case 1:
		Threadtest = new SharedLockingTest(); break;
	}
	if (Threadtest)
	{
		Threadtest->Run();
		delete Threadtest;
	}
	return 0;
}