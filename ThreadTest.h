#pragma once
#include<thread>
#include<chrono>
using namespace std;
class ThreadTest
{
	public:
	ThreadTest() = default;
	virtual ~ThreadTest() = default;
	virtual void Run() = 0;
};
class MeasureDurationUtils
{
public:
	void Measure_Start()
	{
		m_startTime = chrono::steady_clock::now();
	}
	void Measure_End()
	{
		m_endTime = chrono::steady_clock::now();
	}
	auto GetDurationMillisecounds() const
	{
		return chrono::duration_cast<chrono::milliseconds>(m_endTime - m_startTime).count();
	}
private:
	chrono::steady_clock::time_point m_startTime;
	chrono::steady_clock::time_point m_endTime;
};
