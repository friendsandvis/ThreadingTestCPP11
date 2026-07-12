#pragma once
#include "ThreadTest.h"
#include<string>
#include<shared_mutex>
#include<mutex>
#include<vector>
#include<queue>
#include<iostream>

template<typename T>
class ThreadSafeQueue
{
public:
	ThreadSafeQueue()
	{

	}
	ThreadSafeQueue(const ThreadSafeQueue& other) = delete;
	ThreadSafeQueue(const ThreadSafeQueue&& other) = delete;
	void Push(T& entry)
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		m_queue.push(entry);
	}
	bool Pop(T& popedEntry)
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		if (!m_queue.empty())
		{
			popedEntry = m_queue.front();
			m_queue.pop();
			return true;
		}
		return false;
	}
	bool ISEmpty()
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		return m_queue.empty();
	}
	size_t GetElementCount()
	{
		std::lock_guard<std::mutex> lock(m_mtx);
		return m_queue.size();
	}
private:

	std::mutex m_mtx;
	std::queue<T> m_queue;
};
class QueueTest : public ThreadTest
{
public:
	void Run() override;
	void AddTask(int startNum, int endNum);
	void DisplayTask();
private:
	static mutex printMtx;
	vector<thread> m_threadsInAction;
	ThreadSafeQueue<int> m_testQueue;
};