#pragma once
#include "DiningPhilosopherTestCommon.h"
class DiningPhilosopherLiveLockTest : public ThreadTest
{
public:
	struct Philosopher
	{
		Philosopher(std::string name, int leftForkId, int rightForkId) :
			name(name),
			leftForkIdx(leftForkId),
			rightForkIdx(rightForkId)
		{
		}
		string name;
		int EatedCount = 0;
		int leftForkIdx;
		int rightForkIdx;
	};
	struct Fork
	{
		void SetName(string forkName)
		{
			name = forkName;
		}
		string name;
		mutex m;

	};
	void Run() override;
	static void PhilosopherTryEatBasic(const int philosepherIdx);
	static void PhilosopherTryEatLockBothForkTogether(const int philosepherIdx);
	// lock 1 fork and unlock if other fork not available
	static void PhilosopherEatLivelocked(const int philosepherIdx);
private:
	static mutex printMtx;
	static void PhilosopherWork(const int philosepherIdx);
	static vector<Philosopher> philosophers;
	static array<Fork, NUMFORKS> forks;
	vector<thread> m_philosopherAtWork;

};
