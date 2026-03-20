#include"DownloadConditionVariableTest.h"

string DownloadConditionVariableTest::downloadedData;
mutex DownloadConditionVariableTest::downloadingDataMtx;
mutex DownloadConditionVariableTest::downloadingCompleteMtx;
mutex DownloadConditionVariableTest::printMtx;
bool DownloadConditionVariableTest::downloadComplete;
bool DownloadConditionVariableTest::downloadDataUpdated;

void DownloadConditionVariableTest::Run()
{
	//init
	downloadedData = "";
	downloadComplete = false;
	downloadComplete = false;
	thread downloadThread(DownloadWork);
	m_threadsInAction.push_back(move(downloadThread));
	thread progressBarThread(ProgressBarWork);
	m_threadsInAction.push_back(move(progressBarThread));
	thread processDataThread(ProcessDownloaddedWork);
	m_threadsInAction.push_back(move(processDataThread));
	for (thread& t : m_threadsInAction)
	{
		t.join();
	}
}
void DownloadConditionVariableTest::DownloadWork()
{
	const int maxDownloadCycles = 20;
	for (int i = 0; i < maxDownloadCycles; i++)
	{
		lock_guard<mutex> downloadDataLock(downloadingDataMtx);
		downloadedData += "data chunk " + to_string(i);
		downloadDataUpdated = true;
		this_thread::sleep_for(chrono::milliseconds(2));
	}
	downloadComplete = true;
	{
		lock_guard<mutex> printLock(printMtx);
		cout << "downloading end\n";
	}
}
void DownloadConditionVariableTest::ProgressBarWork()
{
	bool progressBarRunning = true;
	int downloadedSize = 0;
	//start progressbar loop
	while (progressBarRunning)
	{
		//wait for download to be updated
		unique_lock<mutex> downloadDataLock(downloadingDataMtx);
		while (!downloadDataUpdated)
		{
			//unloack and sleep to give room to download
			downloadDataLock.unlock();
			this_thread::sleep_for(chrono::milliseconds(2));
			//lock as we check condition again
			downloadDataLock.lock();
		}
		//download updated so update progress as well
		downloadedSize = downloadedData.size();
		{
			lock_guard<mutex> downloadcompleteLock(downloadingCompleteMtx);
			progressBarRunning = !downloadComplete;
		}
		downloadDataUpdated = false;
		//print progress
		{
			lock_guard<mutex> printLock(printMtx);
			cout << "progress update:::Downloaded size:- " << downloadedSize << " bytes\n";
		}
	}
	{
		lock_guard<mutex> printLock(printMtx);
		cout << "progress bar end\n";
	}
}
void DownloadConditionVariableTest::ProcessDownloaddedWork()
{
	string downloadedDataCopy;
	unique_lock<mutex> downloadCompleteLock(downloadingCompleteMtx);
	while (!downloadComplete)
	{
		//unloack and sleep to give room to download
		downloadCompleteLock.unlock();
		this_thread::sleep_for(chrono::milliseconds(1));
		//lock as we check condition again
		downloadCompleteLock.lock();
	}
	//download complete process
	{
		lock_guard<mutex> dataLock(downloadingDataMtx);
		downloadedDataCopy = downloadedData;
	}
	{
		lock_guard<mutex> printLock(printMtx);
		cout << "Process Downloaded data :::content:-\n" << downloadedDataCopy;
	}

}