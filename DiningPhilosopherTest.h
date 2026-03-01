#pragma once
#include "ThreadTest.h"
#include<string>
#include<mutex>
#include<vector>
#include<chrono>
#include<iostream>
#include<array>
#define NUMPHILOSOPHERS 5
#define NUMFORKS 5
class DiningPhilosopherTest : public ThreadTest
{
public:
	struct Philosopher
	{
		Philosopher(std::string name,int leftForkId, int rightForkId) : 
			name(name),
			leftForkIdx(leftForkId),
			rightForkIdx(rightForkId)
		{}
		string name;
		int EatedCount = 0;
		int leftForkIdx;
		int rightForkIdx;
	};
	struct Fork
	{
		Fork() = default;
		Fork(string forkName)
		:name(forkName)
		{}
		Fork(const char* forkName)
			:name(forkName)
		{
		}
		void SetName(string forkName)
		{
			name = forkName;
		}
		string name;
		mutex m;

	};
	void Run() override;
	static void PhilosopherTryEatBasic(const int philosepherIdx);
private:
	static void PhilosopherWork(const int philosepherIdx);
	static vector<Philosopher> philosophers;
	static array<Fork,NUMFORKS> forks;
	vector<thread> m_philosopherAtWork;
};
