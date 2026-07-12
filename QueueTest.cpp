#include"QueueTest.h"
void QueueTest::Run()
{
	//add 21 elements to queue in 2 threads parallely all display until que uis empty in another thread.
	std::thread adder1(&QueueTest::AddTask, this, 1, 10);
	std::thread adder2(&QueueTest::AddTask, this, 50, 60);
	m_threadsInAction.push_back(std::move(adder1));
	m_threadsInAction.push_back(std::move(adder2));
	std::thread displayQueue(&QueueTest::DisplayTask, this);
	m_threadsInAction.push_back(std::move(displayQueue));
	for (thread& t : m_threadsInAction)
	{
		t.join();
	}
}

void QueueTest::AddTask(int startNum, int endNum)
{
	std::this_thread::sleep_for(chrono::milliseconds(10));
	for(int i= startNum; i <= endNum; i++)
	{
		m_testQueue.Push(i);
	}
}

void QueueTest::DisplayTask()
{
	std::this_thread::sleep_for(chrono::milliseconds(100));
	while (!m_testQueue.ISEmpty())
	{
		int element;
		bool popSuccess = m_testQueue.Pop(element);
		if (popSuccess)
		{
			std::cout << element << std::endl;
			std::this_thread::sleep_for(chrono::milliseconds(10));
		}
	}
}