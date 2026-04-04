#pragma once
#include "ThreadTest.h"
#include<string>
#include<shared_mutex>
#include<mutex>
#include<vector>
#include<iostream>
class AtomicOperationTest : public ThreadTest
{
public:
	void Run() override;
private:
	static void ThreadWork1();
	static void ThreadWork2();
	static mutex printMtx;
	vector<thread> m_threadsInAction;
};