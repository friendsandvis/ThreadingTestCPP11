#include"ThreadPoolTest.h"
//total time should be relative to num threads used as task is added to queue one after another(so distributed)
#define NUMTHREADSINPOOL 2
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
	std::this_thread::sleep_for(chrono::milliseconds(900));
	bool workerAlive = true;
	bool forceExit = false;
	while (workerAlive)
	{
		if (WorkerThreadCanExit(workerIDX))
		{
			break;
		}
		else
		{
			
			bool foundWork = false;
			int numRetryBeforeSteal = 50;
			while (!foundWork)
			{
				
				if (HasOwnWorkRemaining(workerIDX))
				{
					Task task;
					m_taskQueue[workerIDX].Pop(task);
					foundWork = true;
					task();
				}
				else
				{
					//wait to get own work soon or steal
					// add actual steel function to when not getting own work after retries.
					std::this_thread::sleep_for(chrono::milliseconds(100));
					--numRetryBeforeSteal;
					if (numRetryBeforeSteal <= 0)
					{
						forceExit = true;
						break;
					}

				}
				std::this_thread::sleep_for(chrono::milliseconds(50));
			}

			if (forceExit)
			{
				//not finding any work to do exit thread loop
				break;
			}
		}
	}
}

bool ThreadPool::WorkerThreadCanExit(unsigned int workerIDX)
{
	bool result = false;
	bool allQueueEmpty = true;
	for (unsigned int i = 0; i < m_numThreads; i++)
	{
		const bool empty = m_taskQueue[i].ISEmpty();
			allQueueEmpty &= empty;
	}
	result = allQueueEmpty;
	return result;
}

bool ThreadPool::HasOwnWorkRemaining(unsigned int workerIDX)
{
	return (!m_taskQueue[workerIDX].ISEmpty());
}
void ThreadPool::AddTask(Task aTask)
{
		m_taskQueue[selectedThreadTaskAdd].Push(aTask);
		selectedThreadTaskAdd = (selectedThreadTaskAdd + 1) % m_numThreads;
}

void ThreadPool::AddTaskToThread(Task aTask, unsigned int threadIDX)
{
	m_taskQueue[threadIDX].Push(aTask);
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
	Task shortTask = []()
		{
			std::cout << "task started on thread:" << std::this_thread::get_id() << '\n';
			std::this_thread::sleep_for(chrono::milliseconds(50));
			std::cout << "task ended on thread:" << std::this_thread::get_id() << '\n';
		};
	Task longTask = []()
		{
			std::cout << "long task started on thread:" << std::this_thread::get_id() << '\n';
			std::this_thread::sleep_for(chrono::milliseconds(30000));
			std::cout << "task ended on thread:" << std::this_thread::get_id() << '\n';
		};
	for (int i = 0; i < 70; i++)
	{
		//m_testPool.AddTask(shortTask);
		m_testPool.AddTaskToThread(shortTask, 0);
		m_testPool.AddTaskToThread(shortTask, 1);
	}
	m_testPool.AddTaskToThread(longTask,0);
	for (int i = 0; i < 70; i++)
	{
		m_testPool.AddTaskToThread(shortTask, 0);
	}
	m_testPool.JoinAllThreads();
}