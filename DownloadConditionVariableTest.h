#pragma once
#include "ThreadTest.h"
#include<string>
#include<shared_mutex>
#include<mutex>
#include<vector>

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
	static bool downloadComplete;
	static bool downloadDataUpdated;
	static string downloadedData;

	vector<thread> m_threadsInAction;
};
