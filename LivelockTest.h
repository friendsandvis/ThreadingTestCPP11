#pragma once
#include "ThreadTest.h"
#include<string>
#include<shared_mutex>
#include<mutex>
#include<vector>

#include<iostream>
class LiveLockTest : public ThreadTest
{
public:
	void Run() override;
private:
	static void UserWorkA();
	static void UserWorkB();
	static mutex mtx1;
	static mutex mtx2;
	static mutex printMtx;
	vector<thread> m_threadsInAction;
};
