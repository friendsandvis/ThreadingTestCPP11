#include"DiningPhilosopherLiveLockTest.h"
vector<DiningPhilosopherLiveLockTest::Philosopher> DiningPhilosopherLiveLockTest::philosophers =
{
	{"A",0,1},
	{"B",1,2},
	{"C",2,3},
	{"D",3,4},
	{"E",4,0}
};
array<DiningPhilosopherLiveLockTest::Fork, NUMFORKS> DiningPhilosopherLiveLockTest::forks;
mutex DiningPhilosopherLiveLockTest::printMtx;
void DiningPhilosopherLiveLockTest::Run()
{
	//set fork names
	for (unsigned int i = 0; i < NUMFORKS; i++)
	{
		forks[i].SetName("Fork" + to_string(i));
	}
	//start all phelosopher thread to work
	m_philosopherAtWork.push_back(move(thread(PhilosopherWork, 0)));
	m_philosopherAtWork.push_back(move(thread(PhilosopherWork, 1)));
	m_philosopherAtWork.push_back(move(thread(PhilosopherWork, 2)));
	m_philosopherAtWork.push_back(move(thread(PhilosopherWork, 3)));
	m_philosopherAtWork.push_back(move(thread(PhilosopherWork, 4)));
	for (auto& aThread : m_philosopherAtWork)
	{
		aThread.join();
	}
}
void DiningPhilosopherLiveLockTest::PhilosopherWork(const int philosepherIdx)
{

	const int maxWorkCycles = 1;
	int numWorkCycles = maxWorkCycles;//negitive value results infinite loop
	while (numWorkCycles != 0)
	{
		//think sleep
		this_thread::sleep_for(chrono::milliseconds(100));
		//try eat
		PhilosopherEatLivelocked(philosepherIdx);//PhilosopherTryEatLockBothForkTogether(philosepherIdx);

		numWorkCycles--;
	}
}
void DiningPhilosopherLiveLockTest::PhilosopherTryEatBasic(const int philosepherIdx)
{
	Philosopher& philosopher = philosophers[philosepherIdx];
	Fork& leftFork = forks[philosopher.leftForkIdx];
	Fork& rightFork = forks[philosopher.rightForkIdx];
	unique_lock<mutex> leftForkLock(leftFork.m, std::defer_lock);
	unique_lock<mutex> rightForkLock(rightFork.m, std::defer_lock);
	//locking both fork success then able to eat
	leftForkLock.lock();
	{
		lock_guard<mutex> printLock(printMtx);
		std::cout << philosopher.name << " locking left fork" << '\n';

	}
	rightForkLock.lock();

	{
		lock_guard<mutex> printLock(printMtx);
		std::cout << philosopher.name << " locking right fork" << '\n';
	}
	this_thread::sleep_for(chrono::seconds(1));
	philosopher.EatedCount++;
	{
		lock_guard<mutex> printLock(printMtx);
		std::cout << philosopher.name << "eating" << '\n';
	}
}
void DiningPhilosopherLiveLockTest::PhilosopherTryEatLockBothForkTogether(const int philosepherIdx)
{
	Philosopher& philosopher = philosophers[philosepherIdx];
	Fork& leftFork = forks[philosopher.leftForkIdx];
	Fork& rightFork = forks[philosopher.rightForkIdx];
	unique_lock<mutex> leftForkLock(leftFork.m, std::defer_lock);
	unique_lock<mutex> rightForkLock(rightFork.m, std::defer_lock);
	//locking both fork success then able to eat
	std::lock(leftForkLock, rightForkLock);
	{
		lock_guard<mutex> printLock(printMtx);
		std::cout << philosopher.name << " locking left fork and right fork together" << '\n';
	}
	this_thread::sleep_for(chrono::seconds(1));
	philosopher.EatedCount++;
	{
		lock_guard<mutex> printLock(printMtx);
		std::cout << philosopher.name << "eating" << '\n';
	}
}
void DiningPhilosopherLiveLockTest::PhilosopherEatLivelocked(const int philosepherIdx)
{
	Philosopher& philosopher = philosophers[philosepherIdx];
	Fork& leftFork = forks[philosopher.leftForkIdx];
	Fork& rightFork = forks[philosopher.rightForkIdx];
	bool leftForkLocked = false;
	bool rightForkLocked = false;
	while (!rightForkLocked)
	{
		//lock left fork
		leftFork.m.lock();
		{
			lock_guard<mutex> printLock(printMtx);
			std::cout << philosopher.name << " locked left fork" << '\n';
		}
		leftForkLocked = true;
		//try locking right fork too
		if (rightForkLocked = rightFork.m.try_lock())
		{
			lock_guard<mutex> printLock(printMtx);
			std::cout << philosopher.name << " eating" << '\n';
			//eatiing so drop both fork after eating
			leftFork.m.unlock();
			leftForkLocked = false;
			rightFork.m.unlock();
			rightForkLocked = false;
		}
		else
		{
			if (leftForkLocked)
			{
				lock_guard<mutex> printLock(printMtx);
				std::cout << philosopher.name << " cannot lock right fork but left only hence unlock left fork wait and try again" << '\n';
				leftFork.m.unlock();
				leftForkLocked = false;
				this_thread::sleep_for(chrono::milliseconds(100));
			}
		}
		//waited after unlocking locked one as failed to lock both then try again.
	}
	if (leftForkLocked && rightForkLocked)
	{
		//eat if able to lock left  then right fork
		this_thread::sleep_for(chrono::milliseconds(100));
		philosopher.EatedCount++;
		lock_guard<mutex> printLock(printMtx);
		std::cout << philosopher.name << " is eating" << '\n';
	}
	if (leftForkLocked)
	{
		leftFork.m.unlock();
	}
	if (rightForkLocked)
	{
		rightFork.m.unlock();
	}
}