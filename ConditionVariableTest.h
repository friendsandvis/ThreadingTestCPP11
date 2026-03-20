#pragma once
#include "ThreadTest.h"
#include<string>
#include<condition_variable>
#include<mutex>
#include<vector>

#include<iostream>
class ConditionVariableTest : public ThreadTest
{
public:
	void Run() override;
private:
	static void ProducerWork();
	static void ConsumerWork();
	static mutex mtx;
	static mutex printMtx;
	static string sharedStr;
	static condition_variable conditionVar;
	vector<thread> m_threadsInAction;
};
