#include"AtomicOperationTest.h"

mutex AtomicOperationTest::printMtx;
unsigned int AtomicOperationTest::m_sharedValue = 0;
atomic<unsigned int> AtomicOperationTest::m_sharedValue_atomicVar = 0;
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
	{
		lock_guard<mutex> lock(printMtx);
		cout << "Final value of shared variable: " << m_sharedValue << endl;
		cout << "Final value of shared variable(atomic): " << m_sharedValue_atomicVar << endl;
	}
}
void AtomicOperationTest::ThreadWork1()
{
	for (unsigned int i = 0; i < 1000000; i++)
	{
		m_sharedValue++;
		m_sharedValue_atomicVar++;
	}
}
void AtomicOperationTest::ThreadWork2()
{
	for (unsigned int i = 0; i < 1000000; i++)
	{
		m_sharedValue++;
		m_sharedValue_atomicVar++;
	}
}