#pragma once
#include "ThreadTest.h"
#include<string>
#include<shared_mutex>
#include<mutex>
#include<vector>
#include<condition_variable>
#include<iostream>
class DownloadConditionVariableTest : public ThreadTest
{
public:
	void Run() override;
private:
	static void DownloadWork();
	static void ProgressBarWork();
	static void ProcessDownloaddedWork();
	static mutex downloadingDataMtx;
	static mutex downloadingCompleteMtx;
	static mutex printMtx;
	static condition_variable downloadCompleteConditionVar;
	static condition_variable downloadDataUpdatedConditionVar;
	static bool downloadDataUpdated;
	static bool downloadCompleted;
	static string downloadedData;

	vector<thread> m_threadsInAction;
};
