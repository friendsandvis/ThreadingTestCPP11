#include"DiningPhilosopherSolvedTest.h"
vector<DiningPhilosopherSolvedTest::Philosopher> DiningPhilosopherSolvedTest::philosophers =
{
	{"A",0,1},
	{"B",1,2},
	{"C",2,3},
	{"D",3,4},
	{"E",4,0}
};
array<DiningPhilosopherSolvedTest::Fork, NUMFORKS> DiningPhilosopherSolvedTest::forks;
void DiningPhilosopherSolvedTest::Run()
{
	//set fork names
	for (unsigned int i = 0; i < NUMFORKS; i++)
	{
		forks[i].SetName("Fork" + to_string(i));
	}
	//start all phelosopher thread to work
	for (int i = 0; i < NUMPHILOSOPHERS; i++)
	{
		thread philosopherThread(PhilosopherWork, i);
		m_philosopherAtWork.push_back(move(philosopherThread));
	}
	for (auto& aThread : m_philosopherAtWork)
	{
		aThread.join();
	}
}
void DiningPhilosopherSolvedTest::PhilosopherWork(const int philosepherIdx)
{

	const int maxWorkCycles = 1;
	int numWorkCycles = maxWorkCycles;//negitive value results infinite loop
	while (numWorkCycles != 0)
	{
		//think sleep
		this_thread::sleep_for(chrono::seconds(2));
		//try eat
		PhilosopherTryEatLockBothForkTogether(philosepherIdx);

		numWorkCycles--;
	}
}
void DiningPhilosopherSolvedTest::PhilosopherTryEatBasic(const int philosepherIdx)
{
	Philosopher& philosopher = philosophers[philosepherIdx];
	Fork& leftFork = forks[philosopher.leftForkIdx];
	Fork& rightFork = forks[philosopher.rightForkIdx];
	unique_lock<mutex> leftForkLock(leftFork.m, std::defer_lock);
	unique_lock<mutex> rightForkLock(rightFork.m, std::defer_lock);
	//locking both fork success then able to eat
	leftForkLock.lock();
	{
		std::cout << philosopher.name << " locking left fork" << '\n';
	}
	rightForkLock.lock();

	{
		std::cout << philosopher.name << " locking right fork" << '\n';
	}
	this_thread::sleep_for(chrono::seconds(1));
	philosopher.EatedCount++;
	std::cout << philosopher.name << "eating" << '\n';
}
void DiningPhilosopherSolvedTest::PhilosopherTryEatLockBothForkTogether(const int philosepherIdx)
{
	Philosopher& philosopher = philosophers[philosepherIdx];
	Fork& leftFork = forks[philosopher.leftForkIdx];
	Fork& rightFork = forks[philosopher.rightForkIdx];
	unique_lock<mutex> leftForkLock(leftFork.m, std::defer_lock);
	unique_lock<mutex> rightForkLock(rightFork.m, std::defer_lock);
	//locking both fork success then able to eat
	std::lock(leftForkLock, rightForkLock);
	{
		std::cout << philosopher.name << " locking left fork and right fork together" << '\n';
	}
	this_thread::sleep_for(chrono::seconds(1));
	philosopher.EatedCount++;
	std::cout << philosopher.name << "eating" << '\n';
}