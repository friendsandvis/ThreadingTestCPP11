#include"SharedlockingTest.h"

string SharedLockingTest::m_sharedResource;
mutex SharedLockingTest::m_sharedResourceMutex_simple;
shared_mutex SharedLockingTest::m_sharedResourceMutex_shared;
void SharedLockingTest::Run()
{
	const unsigned int numReaderThreads = 30;
	const unsigned int numWriterThreads = 1;
	for (unsigned int i = 0; i < numWriterThreads; i++)
	{
		thread writerThread(SharedLockingTest::ModifySharedResource);
		m_threadsInAction.push_back(move(writerThread));
	}
	for (unsigned int i = 0; i < numReaderThreads; i++)
	{
		thread readerThread(SharedLockingTest::AccessSharedResource);
		m_threadsInAction.push_back(move(readerThread));
	}
	for (auto& aThread : m_threadsInAction)
	{
		aThread.join();
	}
}
void SharedLockingTest::ModifySharedResource()
{
	unique_lock<shared_mutex> lock_uniqueLock(m_sharedResourceMutex_shared, std::defer_lock);
	if (!lock_uniqueLock.try_lock())
	{
		//not able to lock print
	}
	m_sharedResource = "Modified";
	//cout << "Shared resource modified" << '\n';
}
void SharedLockingTest::AccessSharedResource()
{
	shared_lock<shared_mutex> lock_sharedLock(m_sharedResourceMutex_shared, std::defer_lock);
	if (!lock_sharedLock.try_lock())
	{
		//not able to lock print
	}
	//cout << "Shared resource reading start" << '\n';
	this_thread::sleep_for(chrono::seconds(1));
	//cout << "Shared resource reading end" << '\n';

}