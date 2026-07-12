#pragma once
#include "ThreadTest.h"
#include<iostream>
#include"ThreadSafeQueue.h"
class QueueTest : public ThreadTest
{
public:
	void Run() override;
	void AddTask(int startNum, int endNum);
	void DisplayTask();
private:
	static mutex printMtx;
	vector<thread> m_threadsInAction;
	ThreadSafeQueue<int> m_testQueue;
};