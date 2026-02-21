#pragma once
#include<thread>

using namespace std;
class ThreadTest
{
	public:
	ThreadTest() = default;
	virtual ~ThreadTest() = default;
	virtual void Run() = 0;
};
