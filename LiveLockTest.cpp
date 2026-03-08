#include"LivelockTest.h"

mutex LiveLockTest::mtx1;
mutex LiveLockTest::mtx2;
mutex LiveLockTest::printMtx;
void LiveLockTest::Run()
{
	m_threadsInAction.push_back(move(thread(UserWorkA)));
	this_thread::sleep_for(chrono::milliseconds(50));
	m_threadsInAction.push_back(move(thread(UserWorkB)));
	for (auto& aThread : m_threadsInAction)
	{
		aThread.join();
	}
}
//lock order is mtx 1 then mtx 2
void LiveLockTest::UserWorkA()
{
	bool mtx2Locked = false;
	bool mtx1Locked = false;
	//lock mtx 1
	mtx1.lock();
	{
		mtx1Locked = true;
		{
			cout << "worker A locked Mutex 1\n";
		}
	}
	while (!mtx2Locked)
	{
		this_thread::sleep_for(chrono::milliseconds(100));
		//try lock mtx 2
		{
			cout << "Worker A trying to lock mutex 2 to work\n";
		}
		if (mtx2Locked = mtx2.try_lock())
		{
			if (mtx1Locked)
			{
				cout << "worker A can work. \n";
			}
		}
	}
	if (mtx1Locked)
	{
		mtx1.unlock();
	}
	if (mtx2Locked)
	{
		mtx2.unlock();
	}
}


//lock order is mtx 2 then mtx 1 opposite of worker A understand like opnening 2 doors to get obj but workers trying from opposit sides.
void LiveLockTest::UserWorkB()
{
	bool mtx2Locked = false;
	bool mtx1Locked = false;
	//lock mtx 2
	mtx2.lock();
	{
		mtx2Locked = true;
		cout << "Worker B locked mutex 2\n";
	}
	while (!mtx1Locked)
	{
		this_thread::sleep_for(chrono::milliseconds(10));
		//try lock mtx 1
		{
			cout << "Worker B trying to lock mutex 1 to work\n";
		}
		if (mtx1Locked = mtx1.try_lock())
		{
			if (mtx2Locked)
			{
				cout << "Worker B can work\n";
			}
		}
	}
	if (mtx1Locked)
	{
		mtx1.unlock();
	}
	if (mtx2Locked)
	{
		mtx2.unlock();
	}
}