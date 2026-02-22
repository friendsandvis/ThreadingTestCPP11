#pragma once
#include "ThreadTest.h"
#include<string>
#include<shared_mutex>
#include<mutex>
#include<vector>

#include<iostream>
class SharedLockingTest: public ThreadTest
{
public:
	void Run() override;
private:
	static void AccessSharedResource();
	static void ModifySharedResource();
	static string m_sharedResource;
	static shared_mutex m_sharedResourceMutex_shared;
	static mutex m_sharedResourceMutex_simple;
	vector<thread> m_threadsInAction;
};
