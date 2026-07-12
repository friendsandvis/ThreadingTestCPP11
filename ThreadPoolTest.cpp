#include"ThreadPoolTest.h"
//total time should be relative to num threads used as task is added to queue one after another(so distributed)
#define NUMTHREADSINPOOL 6
#define NUMTESTTASK 60
ThreadPool::ThreadPool(unsigned int numThreads)
{
	m_numThreads = numThreads;
	m_taskQueue = new ThreadSafeQueue<Task>[numThreads];
	for(unsigned int i = 0; i < numThreads; ++i)
	{
		m_workerThreads.emplace_back(&ThreadPool::WorkerFunction, this, i);
	}
}

ThreadPool::~ThreadPool()
{
	delete[] m_taskQueue;
}
void ThreadPool::WorkerFunction(unsigned int workerIDX)
{
	std::this_thread::sleep_for(chrono::milliseconds(600));
	bool workerAlive = true;
	while (workerAlive)
	{
		if (m_taskQueue[workerIDX].ISEmpty())
		{
			break;
		}
		else
		{
			Task task;
			m_taskQueue[workerIDX].Pop(task);
			task();
			std::this_thread::sleep_for(chrono::milliseconds(50));
		}
	}
}

void ThreadPool::AddTask(Task aTask)
{
		m_taskQueue[selectedThreadTaskAdd].Push(aTask);
		selectedThreadTaskAdd = (selectedThreadTaskAdd + 1) % m_numThreads;
}

void ThreadPool::JoinAllThreads()
{
	for (std::thread& t : m_workerThreads)
	{
		t.join();
	}
}

ThreadPoolTest::ThreadPoolTest()
	:m_testPool(NUMTHREADSINPOOL)
{

}
void ThreadPoolTest::Run()
{
	Task t1 = []()
		{
			std::cout << "task started on thread:" << std::this_thread::get_id() << '\n';
			std::this_thread::sleep_for(chrono::milliseconds(300));
			std::cout << "task ended on thread:" << std::this_thread::get_id() << '\n';
		};
	for (int i = 0; i < NUMTESTTASK; i++)
	{
		m_testPool.AddTask(t1);
	}
	m_testPool.JoinAllThreads();
}