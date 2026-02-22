#include<iostream>
#include"SharedlockingTest.h"
#include"NormallockingTest.h"

int main()
{
	cout << "Treading Test to run:\n";
	cout << "1. ReaderWriter_sharedMutexTest\n";
	cout << "2. ReaderWriter_normalMutexTest\n";
	cout << "Please input the test number to run:\n";
	int testNum;
	ThreadTest* Threadtest = nullptr;
	cin >> testNum;
	switch (testNum)
	{
	case 1:
		Threadtest = new SharedLockingTest(); break;
	case 2:
		Threadtest = new NormalLockingTest(); break;
	}
	if (Threadtest)
	{
		MeasureDurationUtils threadRunDuration;
		threadRunDuration.Measure_Start();
		Threadtest->Run();
		threadRunDuration.Measure_End();
		cout << "Test duration: " << threadRunDuration.GetDurationMillisecounds() << " ms\n";
		delete Threadtest;
	}
	return 0;
}