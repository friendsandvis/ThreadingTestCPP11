#pragma once
#include "ThreadTest.h"
#include<string>
#include<shared_mutex>
#include<mutex>
#include<vector>
#include<future>
#include<iostream>
class PackedTaskTest : public ThreadTest
{
public:
	void Run() override;
private:
	void RunTaskImmidiate(packaged_task<int(int, int, char)> task);
	void RunTaskInOtherThread(packaged_task<int(int, int, char)> task);
	vector<thread> m_threadsInAction;
};