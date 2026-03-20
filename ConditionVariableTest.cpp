#include"ConditionVariableTest.h"

 mutex ConditionVariableTest::mtx;
 mutex ConditionVariableTest::printMtx;
string ConditionVariableTest::sharedStr="empty";
condition_variable ConditionVariableTest::conditionVar;
void ConditionVariableTest::Run()
{
	std::thread producerThread(ProducerWork);
	m_threadsInAction.push_back(std::move(producerThread));
	std::thread consumerThread(ConsumerWork);
	m_threadsInAction.push_back(std::move(consumerThread));

	for (thread& t : m_threadsInAction)
	{
		t.join();
	}
}
void ConditionVariableTest::ProducerWork()
{
	{
		lock_guard<mutex>  mtxLock(mtx);
		//read shared str then modify for consumer
		{
			lock_guard<mutex> printLock(printMtx);
			std::cout << "producer reads string: " << sharedStr << " then modifies\n";
		}
		sharedStr = "modified";
	}
	//releasing shared mtx locck before nortify avoids slow execiution in waiting one.
	conditionVar.notify_all();
}
void ConditionVariableTest::ConsumerWork()
{
	unique_lock<mutex> mtxLock(mtx);
	//wait for condition variable before reading shared data
	conditionVar.wait(mtxLock);
	{
		lock_guard<mutex> printLock(printMtx);
		std::cout << "consumer reads string: " << sharedStr << '\n';
	}

}