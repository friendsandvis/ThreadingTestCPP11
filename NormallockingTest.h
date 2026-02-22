#pragma once
#include "ThreadTest.h"
#include<string>
#include<mutex>
#include<vector>
#include<chrono>
#include<iostream>
class NormalLockingTest: public ThreadTest
{
public:
	void Run() override;
private:
	static void AccessSharedResource();
	static void ModifySharedResource();
	static string m_sharedResource;
	static mutex m_sharedResourceMutex_simple;
	vector<thread> m_threadsInAction;
};
