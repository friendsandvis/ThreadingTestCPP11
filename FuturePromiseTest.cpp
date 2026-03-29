#include"FuturePromiseTest.h"
#include<string>
mutex FuturePromiseTest::printMtx;
void FuturePromiseTest::Run()
{
	promise<string> producedStrPromise;
	future<string> producedStrFuture = producedStrPromise.get_future();
	thread producerThread(ProduceWork, std::ref(producedStrPromise));
	thread consumerThread(ConsumeWork, std::ref(producedStrFuture));
	m_threadsInAction.push_back(move(producerThread));
	m_threadsInAction.push_back(move(consumerThread));

	for (thread& t : m_threadsInAction)
	{
			t.join();
	}
}

void FuturePromiseTest::ProduceWork(promise<string>& dataPromise)
{
	string producedData("ProducedData\n");
	{
		lock_guard<mutex> printLock(printMtx);
		cout << "producer Starts\n";
	}
	this_thread::sleep_for(chrono::seconds(3));
	
	{
		lock_guard<mutex> printLock(printMtx);
		cout << "producer sets data: " << producedData << '\n';
	}
	dataPromise.set_value(producedData);
}
void FuturePromiseTest::ConsumeWork(future<string>& dataFuture)
{
	{
		lock_guard<mutex> printLock(printMtx);
		cout << "consumer Starts to get data\n";
	}
	string producedData = dataFuture.get();
	{
		lock_guard<mutex> printLock(printMtx);
		cout << "consumer got data: " << producedData << '\n';
	}
}