#include"NormallockingTest.h"

string NormalLockingTest::m_sharedResource;
mutex NormalLockingTest::m_sharedResourceMutex_simple;
void NormalLockingTest::Run()
{
	const unsigned int numReaderThreads = 10;
	const unsigned int numWriterThreads = 1;
	for (unsigned int i = 0; i < numWriterThreads; i++)
	{
		thread writerThread(NormalLockingTest::ModifySharedResource);
		m_threadsInAction.push_back(move(writerThread));
	}
	for (unsigned int i = 0; i < numReaderThreads; i++)
	{
		thread readerThread(NormalLockingTest::AccessSharedResource);
		m_threadsInAction.push_back(move(readerThread));
	}
	for (auto& aThread : m_threadsInAction)
	{
		aThread.join();
	}
}
void NormalLockingTest::ModifySharedResource()
{
	lock_guard<mutex> lock_lockGuard(m_sharedResourceMutex_simple);
	m_sharedResource = "Modified";
	//cout << "Shared resource modified" << '\n';
}
void NormalLockingTest::AccessSharedResource()
{
	lock_guard<mutex> lock_lockGuard(m_sharedResourceMutex_simple);
	//cout << "Shared resource reading start" << '\n';
	this_thread::sleep_for(chrono::seconds(1));
	//cout << "Shared resource reading end" << '\n';

}