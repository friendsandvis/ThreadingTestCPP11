#include<iostream>
#include"SharedlockingTest.h"
#include"NormallockingTest.h"
#include"LivelockTest.h"
#include"DiningPhilosopherTest.h"
#include"DiningPhilosopherSolvedTest.h"
#include"DiningPhilosopherLivelockTest.h"
#include"DownloadThreadCoordinationTest.h"

int main()
{
	cout << "Treading Test to run:\n";
	cout << "1. ReaderWriter_sharedMutexTest\n";
	cout << "2. ReaderWriter_normalMutexTest\n";
	cout << "3. dining philosopher problem dead lock test\n";
	cout << "4. dining philosopher problem live lock test\n";
	cout << "5. dining philosopher problem dead lock fix pick fork together.\n";
	cout << "6. live lock simple test.\n";
	cout << "7. downloading thread coordination simple test.\n";
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
	case 3:
		Threadtest = new DiningPhilosopherTest(); break;
	case 4:
		Threadtest = new DiningPhilosopherLiveLockTest(); break;
	case 5:
		Threadtest = new DiningPhilosopherSolvedTest(); break;
	case 6:
		Threadtest = new LiveLockTest(); break;
	case 7:
		Threadtest = new DownloadThreadCoordinationTest(); break;
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