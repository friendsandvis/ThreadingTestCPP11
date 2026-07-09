#pragma once
#include "ThreadTest.h"
#include<string>
#include<shared_mutex>
#include<mutex>
#include<vector>
#include<future>
#include<iostream>

class Semaphore
{
public:
	Semaphore();
	void Aquire();
	void Release();
	void PrintCounter();
private:
	static const unsigned int initialCounter;
	unsigned int m_counter;
	std::mutex m_mutex;
	std::condition_variable m_conditionVar;

};
class SemaphoreTest : public ThreadTest
{
public:
	void Run() override;
	void Task1();
	void Task2();
private:
	static mutex printMtx;
	vector<thread> m_threadsInAction;
	Semaphore m_Semaphore;
};