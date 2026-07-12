#pragma once
#include "ThreadTest.h"
#include<string>
#include<shared_mutex>
#include<mutex>
#include<vector>
#include<iostream>
#include"ThreadSafeQueue.h"
#include<vector>
#include<functional>

using Task = std::function<void()>;//typedef std::function<void(int num1, int num2)> Task;
class ThreadPool
{
public:
	ThreadPool(unsigned int numThreads = 1);
	~ThreadPool();
	void AddTask(Task aTask);
	void JoinAllThreads();

private:

	unsigned int m_numThreads;
	ThreadSafeQueue<Task>* m_taskQueue;
	std::vector<std::thread> m_workerThreads;
	unsigned selectedThreadTaskAdd = 0;

	void WorkerFunction(unsigned int workerIDX);
};
class ThreadPoolTest : public ThreadTest
{
public:
	ThreadPoolTest();
	void Run() override;
private:
	static mutex printMtx;
	ThreadPool m_testPool;
};