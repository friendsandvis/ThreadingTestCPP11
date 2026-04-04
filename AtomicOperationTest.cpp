#include"AtomicOperationTest.h"

mutex AtomicOperationTest::printMtx;
void AtomicOperationTest::Run()
{
	thread thread1(ThreadWork1);
	thread thread2(ThreadWork2);
	m_threadsInAction.push_back(move(thread1));
	m_threadsInAction.push_back(move(thread2));
	for (thread& t : m_threadsInAction)
	{
			t.join();
	}
}
void AtomicOperationTest::ThreadWork1()
{
}
void AtomicOperationTest::ThreadWork2()
{
}