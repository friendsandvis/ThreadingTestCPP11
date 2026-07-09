#include "SemaphoreTest.h"

const unsigned int Semaphore::initialCounter = 2;
Semaphore::Semaphore()
	:m_counter(initialCounter)
{

}
void Semaphore::Aquire()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (m_counter == 0)
	{
		std::cout << "cannot aquire semaphorewith 0 counter" << "\n";
		//wait till counter becomes greater than 0
		m_conditionVar.wait(lock, [this]()
			{ return (m_counter != 0); });
	}
	
	m_counter--;
	std::cout << "aquired semaphore" << "\n";
	PrintCounter();
}

void Semaphore::Release()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_counter++;
	std::cout << "released semaphore" << "\n";
	PrintCounter();
	m_conditionVar.notify_all();
}

void Semaphore::PrintCounter()
{
	std::cout << "Semaphore counter: " << m_counter << '\n';
}
void SemaphoreTest::Run()
{
	//2 aquire threads and 1 release thread to test semaphore
	std::thread task1Thread(&SemaphoreTest::Task1, this);
	m_threadsInAction.push_back(move(task1Thread));
	std::thread task1Thread_extra(&SemaphoreTest::Task1, this);
	m_threadsInAction.push_back(move(task1Thread_extra));
	std::thread task2Thread(&SemaphoreTest::Task2, this);
	m_threadsInAction.push_back(move(task2Thread));

	for (thread& t : m_threadsInAction)
	{
		t.join();
	}
}

void SemaphoreTest::Task1()
{
	this_thread::sleep_for(chrono::milliseconds(1000));
	m_Semaphore.Aquire();
}

void SemaphoreTest::Task2()
{
	for (int i = 0; i <= 6; i++)
	{
		this_thread::sleep_for(chrono::milliseconds(2000));
		m_Semaphore.Release();
	}
}