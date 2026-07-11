#pragma once
#include "ThreadTest.h"
#include<string>
#include<shared_mutex>
#include<mutex>
#include<vector>
#include<iostream>
class ThreadPoolTest : public ThreadTest
{
public:
	void Run() override;
private:
	static mutex printMtx;
	vector<thread> m_threadsInAction;
};