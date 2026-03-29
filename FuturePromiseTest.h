#pragma once
#include "ThreadTest.h"
#include<string>
#include<shared_mutex>
#include<mutex>
#include<vector>
#include<future>
#include<iostream>
class FuturePromiseTest : public ThreadTest
{
public:
	void Run() override;
private:
	static void ProduceWork(promise<string>& dataPromise);
	static void ConsumeWork(future<string>& dataFuture);
	static mutex printMtx;
	vector<thread> m_threadsInAction;
};