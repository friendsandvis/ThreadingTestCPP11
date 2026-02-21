#pragma once
#include "ThreadTest.h"
#include<string>
class SharedLockingTest: public ThreadTest
{
public:
	void Run() override;
private:
	void ModifySharedResource();
	string sharedResource;
};
